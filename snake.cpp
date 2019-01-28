#include "app_config.hpp"

// For the snake, the 'playing field' (display) is twice as small as it actually is
// Because every pixel is actually 4px, 2 horizontal and 2 vertical.
// Otherwise the snake is barely visible

#define SWIDTH (WIDTH/2)
#define SHEIGHT (HEIGHT/2)

static bool init = false;

static Snake snakes[SNAKE_COUNT];
static bool collision[SNAKE_COUNT]; // Whether a collision occurred

// Position of tails of all snakes
static Point snakePositions[SNAKE_COUNT][SNAKE_MAX_LENGTH];

// Run only once, to initialize the structures.
// The initialization is too complex to do with initializer lists, g++ complains
void do_init() {
	Snake *snake = &snakes[0];
	snakePositions[0][0].x = SWIDTH/2;
	snakePositions[0][0].y = SHEIGHT/2;
	snake->len = 10;
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

// State machine for playing Snake
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

/**
 * Was the head of the snake in the same place as the pokemon? If so, grow the snake
 */
void check_pokemon_hits(Point pokemonPosition) {
#pragma HLS inline
	Snake *snake = &snakes[snake_state_counter];
	Point *snakePos = snakePositions[snake_state_counter];
	Point head = snakePos[0];
	if (head.x >= (pokemonPosition.x/2) && head.x <= (pokemonPosition.x + pokesize.x)/2 &&
		head.y >= (pokemonPosition.y/2) && head.y <= (pokemonPosition.y + pokesize.y)/2) {
		snake->len++;
#ifndef __SYNTHESIS__
		printf("Snake %d has grown to %d!\n", snake_state_counter, snake->len);
#endif
	}
}
/**
 * Check whether the player wants the snake to go somewhere else
 */
void parse_user_input(const u8 newDirection[SNAKE_COUNT]) {
#pragma HLS inline
	u8 dir = newDirection[snake_state_counter];
	Snake *snake = &snakes[snake_state_counter];

	// Prevent the snake from turning 180 degrees
	if (custom_abs((u8) snake->dir - dir) != 2) {
		snake->dir = (Direction) dir;
	}
}

/**
 * Move every position of the snake one memory element further
 * To make room for the new 'head' of the snake
 */
void move_snake_through() {
#pragma HLS inline
	printf("Moving snek through\n");
	for (int i = SNAKE_MAX_LENGTH - 1; i > 0; i--) {
#pragma HLS unroll
		snakePositions[snake_state_counter][i].x = snakePositions[snake_state_counter][i-1].x;
		snakePositions[snake_state_counter][i].y = snakePositions[snake_state_counter][i-1].y;
	}
}

/**
 * Add the new 'head' of the snake
 */
void add_current_point() {
#pragma HLS inline
#ifndef __SYNTHESIS__
	printf("Add the new head of the snake\n");
#endif

	const u16 n = 1;
	Snake *snake = &snakes[snake_state_counter];
	Point *oldPoint = &snakePositions[snake_state_counter][1];
	Point *newPoint = &snakePositions[snake_state_counter][0];
	switch (snake->dir) {
	case Left:
		newPoint->x = oldPoint->x - n;
		newPoint->y = oldPoint->y;
		break;

	case Right:
		newPoint->x = oldPoint->x + n;
		newPoint->y = oldPoint->y;
		break;

	case Up:
		newPoint->x = oldPoint->x;
		newPoint->y = oldPoint->y - n;
		break;

	case Down:
		newPoint->x = oldPoint->x;
		newPoint->y = oldPoint->y + n;
		break;
	default:
#ifndef __SYNTHESIS__
		printf("It is impossible to reach the default state for direction\n");
#endif
		break;
	}
}

/**
 * Did the snake crash into another snake?
 */
void parse_crash_snake() {
#pragma HLS inline
	Snake *snake = &snakes[snake_state_counter];
	Point *p = &snakePositions[snake_state_counter][0];
	u16 x = p->x;
	u16 y = p->y;

	/**
	 * Error because of ugly boolean flipping below
	 */
#if SNAKE_COUNT != 2
#error "De snake count is te hoog"
#endif

	Snake* de_andere_snake = &snakes[!snake_state_counter];

	Point *comparison = snakePositions[!snake_state_counter];

	bool local_collision = false;
	for (int i = 0; i < SNAKE_MAX_LENGTH; i++) {
#pragma HLS unroll
		if (comparison[i].x == x && comparison[i].y == y && i < de_andere_snake->len) {
			local_collision = true;
		}
	}
	collision[snake_state_counter] = local_collision;
}

/**
 * Did the snake crash into a wall?
 */
void parse_crash_wall() {
#pragma HLS inline
	Snake *snake = &snakes[snake_state_counter];
	Point *p = &snakePositions[snake_state_counter][0];
	u16 x = snakePositions[snake_state_counter][0].x;
	u16 y = snakePositions[snake_state_counter][0].y;

	// Ugly logic at it again
#if SNAKE_COUNT != 2
#error "De sneek count is te hoog"
#endif
	const bool outOfBounds = (x == 0 || x > (SWIDTH-1) || y == 0 || y > (SHEIGHT-1));
	if (outOfBounds || collision[snake_state_counter]){
		snake->len = 3;
		u16 a = (snakePositions[!snake_state_counter][0].x + SWIDTH/4);
		u16 b = (snakePositions[!snake_state_counter][0].y + SHEIGHT/4);
		snakePositions[snake_state_counter][0].x = a >= SWIDTH ? a-SWIDTH : a;
		snakePositions[snake_state_counter][0].y = b >= SHEIGHT ? b-SHEIGHT : b;
	}
}

/**
 * Do we need to draw a snake at thix pixel?
 */
u32 snake_draw_maybe(u16 x, u16 y) {
#pragma HLS inline
	for (int i = 0; i < SNAKE_COUNT; i++) {
#pragma HLS unroll
		Snake* snake = &snakes[i];
		bool shouldReturnThisSnake = false;
		for (int j = 0; j < SNAKE_MAX_LENGTH; j++) {
#pragma HLS unroll
			Point pos = snakePositions[i][j];
			if (pos.x == x/2 && pos.y == y/2 && j <= snake->len) {
#ifndef __SYNTHESIS__
//				printf("Snake drawn at %d %d\n",x,y);
#endif
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
 * main state machine function
 */
u32 run_snake_machine(const u8 ps[SNAKE_COUNT], bool reset, u16 x, u16 y, Point moved, u8 n_frames) {
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
				printf("{%d,%d}, ", snakePositions[i][j].x, snakePositions[i][j].y);
			}
			printf("]\n");
		}
	}
#endif
	static snake_machine state;
	u16 snake_state_counter_copy = snake_state_counter;

	if (reset) {
//		const int n_frames = 10; // Get from mask instead
		static u8 once_per_n_frames = 0;
		if (once_per_n_frames == n_frames) {
			state = CHECK_POKEMON_HITS;
			once_per_n_frames = 0;
		} else {
			state = WAITING;
			once_per_n_frames++;
		}
		snake_state_counter = 0;
		return 0;
	}
	if (snake_state_counter_copy == SNAKE_COUNT) { // Move state machine through
		switch (state) {
		case CHECK_POKEMON_HITS:
		case HANDLE_USER_INPUT:
		case MOVE_SNAKE_THROUGH:
		case ADD_POINT:
		case PARSE_CRASHES_SNAKE:
		case PARSE_CRASHES_WALL:
			state = (snake_machine) (state + 1);
			break;
		case WAITING:
			if (y > 1) {
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
	// Run state machine
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
		return res;
		break;
	default:
#ifndef __SYNTHESIS__
		printf("It is impossible to reach the default state for the state: %d\n",state);
#endif
		break;
	}
	snake_state_counter=snake_state_counter_copy+1;
	return 0;
}
