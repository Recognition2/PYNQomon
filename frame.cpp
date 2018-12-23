#include "frame.hpp"


void frame_fill(px_t* buf, u16 x, u16 y, px_t px) {

	const u16 newx = (x * SMALL_WIDTH) / WIDTH;
	const u16 newy = (y * SMALL_HEIGHT) / HEIGHT;

	if( x % (WIDTH / SMALL_WIDTH) == 0 && y % (HEIGHT / SMALL_HEIGHT) == 0){
		buf[newx + newy * SMALL_WIDTH] = px;
	} else {
		buf[newx + newy * SMALL_WIDTH] += px;
	}

}

px_t frame_get(px_t* buf, u16 x, u16 y) {
	return buf[x + y * SMALL_WIDTH];
}
