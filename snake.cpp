#include "app_config.hpp"

#define SWIDTH (WIDTH/2)
#define SHEIGHT (HEIGHT/2)

bool init = false;

static Snake snakes[SNAKE_COUNT];
static Point snakePositions[SNAKE_COUNT][SNAKE_MAX_LENGTH];
void do_init() {
	Snake *snake = &snakes[0];
	snakePositions[0][0].x = SWIDTH/2;
	snakePositions[0][0].y = SHEIGHT/2;
	snake->len = 3;
	snake->maxlen = 0;
	snake->color = 0xFFFF0000;
	snake->dir = Right;

	snake = &snakes[1];
	snakePositions[1][0].x = SWIDTH/2 - 100;
	snakePositions[1][0].y = SHEIGHT/2 ;
	snake->len = 3;
	snake->maxlen = 0;
	snake->color = 0xFF00FF00;
	snake->dir = Down;

}
//static Snake snakes[SNAKE_COUNT] = {{
//		.pos = {WIDTH/2, HEIGHT/2},
//		.len = 1,
//		.maxlen = 0,
//		.color = 0xFFFF0000, // red snake
//		.dir = Right
//}, {
//		.pos = {WIDTH/2 - 1, HEIGHT/2},
//		.len = 1,
//		.maxlen = 0,
//		.color = 0xFF00FF00, // green snake
//		.dir = Down
//}};

enum snake_machine {
	CHECK_POKEMON_HITS,
	HANDLE_USER_INPUT,
	MOVE_SNAKE_THROUGH,
	ADD_POINT,
	PARSE_CRASHES_SNAKE,
	PARSE_CRASHES_WALL,
	WAITING,
	CHECKING_INPUTS,
};

static u16 snake_state_counter = 0;
//static Point futurePoints[SNAKE_COUNT];

void check_pokemon_hits(Point moved) {
	for (int i = 0; i < SNAKE_COUNT; i++) {
#pragma HLS unroll
		Snake *snake = &snakes[i];
		Point *snakePos = snakePositions[i];
		Point pos = snakePos[0];
		if (pos.x > (moved.x/2) && pos.x < (moved.x + pokesize.x)/2 &&
			pos.y > (moved.y/2) && pos.y < (moved.y + pokesize.y)/2) {
			snake->len++;
#ifndef __SYNTHESIS__
			printf("Snake %d has grown to %d!\n", i, snake->len);
#endif
		}
	}
}

void parse_user_input(const u8 ps[SNAKE_COUNT]) {
#pragma HLS inline
	u8 dir = ps[snake_state_counter];
	Snake *snake = &snakes[snake_state_counter];
//	u8 tmp = (u8) snake->dir;
//	if ((dir&0x2) == 2) {
//		tmp = (tmp == 3) ? 0 : tmp + 1;
//	} else if ((dir&0x01)) {
//		tmp = (tmp == 0) ? 3 : tmp-1;
//	}

	snake->dir = (Direction) dir;
}

void move_snake_through() {
#pragma HLS inline
	Snake *snake = &snakes[snake_state_counter];
	for (int i = SNAKE_MAX_LENGTH - 2; i >= 0; i--) {
#pragma HLS unroll
		snakePositions[snake_state_counter][i+1].x = snakePositions[snake_state_counter][i].x;
		snakePositions[snake_state_counter][i+1].y = snakePositions[snake_state_counter][i].y;
	}
}

void add_current_point() {
#pragma HLS inline
#ifndef __SYNTHESIS__
	printf("Het huidige point wordt nu toegevoegd\n");
#endif

	Snake *snake = &snakes[snake_state_counter];
	Point *oldPoint = &snakePositions[snake_state_counter][1];
	Point *newPoint = &snakePositions[snake_state_counter][0];
	switch (snake->dir) {
	case Left:
		newPoint->x = oldPoint->x - 1;
		newPoint->y = oldPoint->y;
		break;

	case Right:
		newPoint->x = oldPoint->x + 1;
		newPoint->y = oldPoint->y;
		break;

	case Up:
		newPoint->x = oldPoint->x;
		newPoint->y = oldPoint->y - 1;
		break;

	case Down:
		newPoint->x = oldPoint->x;
		newPoint->y = oldPoint->y + 1;
		break;
	default:
#ifndef __SYNTHESIS__
		printf("It is impossible to reach the default state for direction\n");
#endif
		break;
	}
}

void parse_crash_snake() {
#pragma HLS inline
	Snake *snake = &snakes[snake_state_counter];
	Point *p = &snakePositions[snake_state_counter][0];
	u16 x = p->x;
	u16 y = p->y;

#if SNAKE_COUNT != 2
#error "De sneek count is te hoog"
#endif

	Snake* de_andere_snake = &snakes[!snake_state_counter];

	bool collision = false;
	Point *comparison = snakePositions[!snake_state_counter];

	for (int i = 0; i < SNAKE_MAX_LENGTH; i++) {
#pragma HLS unroll
		if (comparison[i].x == x && comparison[i].y == y && i < de_andere_snake->len) {
			collision = true;
		}
	}
	if (collision) {
		snake->len = 3;
		p->x = (comparison[0].x + SWIDTH/2) % SWIDTH;
		p->y = (comparison[0].y + SHEIGHT/2) % SHEIGHT;
	}

}
void parse_crash_wall() {
#pragma HLS inline
	Snake *snake = &snakes[snake_state_counter];
	Point *p = &snakePositions[snake_state_counter][0];

#if SNAKE_COUNT != 2
#error "De sneek count is te hoog"
#endif
	const bool outOfBoundsX = (p->x == 0 || p->x > (SWIDTH-1)/2);
	const bool outOfBoundsY = ( p->y == 0 || p->y > (SHEIGHT-1)/2);
	if (outOfBoundsX || outOfBoundsY){
		snake->len = 3;
		p->x = (snakePositions[!snake_state_counter][0].x + SWIDTH/2) % SWIDTH;
		p->y = (snakePositions[!snake_state_counter][0].y + SHEIGHT/2) % SHEIGHT;
	}
}
u32 snake_draw_maybe(u16 x, u16 y) {
#pragma HLS inline
	for (int i = 0; i < SNAKE_COUNT; i++) {
#pragma HLS unroll
		Snake* snake = &snakes[i];
		bool shouldReturnThisSnake = false;
		for (int j = 0; j < SNAKE_MAX_LENGTH; j++) {
#pragma HLS unroll
			Point pos = snakePositions[i][j];
			if (pos.x == x/2 && pos.y == y/2 && j < snake->len) {
				shouldReturnThisSnake = true;
			}
		}
		if (shouldReturnThisSnake) {
			return snake->color;
		}
	}
	return 0;
}

/**
 * MAIN MACHIEN
 */
u32 run_snake_machine(const u8 ps[SNAKE_COUNT], bool reset, u16 x, u16 y, Point moved) {
//#pragma HLS array_partition variable=snakes complete
#pragma HLS data_pack variable=snakes struct_level
#pragma HLS array_partition variable=snakePositions complete dim=0
	if (!init) {
		do_init();
		init = true;
		return 0;
	}

#ifndef __SYNTHESIS__
	if (reset) {

		for (int i = 0; i < SNAKE_COUNT; i++) {
			Snake s = snakes[i];

			printf("Position of snake %d (length %d):\n[", i, s.len);
			for (int j = 0; j < s.len; j++) {
				printf("{%d,%d}, ", snakePositions[i][j].x*2, snakePositions[i][j].y*2);
			}
			printf("]\n");
		}
	}
#endif
	static snake_machine state;

	if (reset) {
		snake_state_counter = 0;
		state = CHECK_POKEMON_HITS;
		return 0;
	}
	if (snake_state_counter == SNAKE_COUNT) {
		switch (state) {
		case CHECK_POKEMON_HITS:
		case HANDLE_USER_INPUT:
		case ADD_POINT:
		case MOVE_SNAKE_THROUGH:
		case PARSE_CRASHES_SNAKE:
		case PARSE_CRASHES_WALL:
			state = (snake_machine) (state + 1);
			break;
		case WAITING:
			if (y > 0) {
				state = CHECKING_INPUTS;
			}
			break;
		case CHECKING_INPUTS:
		default:
			break;
		}
		snake_state_counter = 0;
		return 0;
	}
	u32 res;
	switch (state) {
	case CHECK_POKEMON_HITS:
		check_pokemon_hits(moved);
		break;

	case HANDLE_USER_INPUT:
		parse_user_input(ps);
		break;

	case ADD_POINT:
		add_current_point();
		break;

	case MOVE_SNAKE_THROUGH:
		move_snake_through();
		break;

	case PARSE_CRASHES_SNAKE:
		parse_crash_snake();
		break;

	case PARSE_CRASHES_WALL:
		parse_crash_wall();
		break;

	case WAITING:
		snake_state_counter = SNAKE_COUNT;
		return 0;

	case CHECKING_INPUTS:
		res = snake_draw_maybe(x,y);
#ifndef __SYNTHESIS__
		if (res != 0) {
			printf("De slang bestaat! {x: %d, y: %d}: %x\n",x,y,res);
		}
#endif
		return res;
		break;
	default:
#ifndef __SYNTHESIS__
		printf("It is impossible to reach the default state for the state: %d\n",state);
#endif
		break;
	}
	snake_state_counter++;
	return 0;
}
