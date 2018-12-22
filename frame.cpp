#include "frame.hpp"

static u8 lastx = 1;

void frame_fill(px_t* buf, u16 x, u16 y, px_t px) {
	if (lastx != x) {
		buf[x + y * SMALL_WIDTH] = px;
	} else {
		buf[x + y * SMALL_WIDTH] += px;
	}
	lastx = x;
}

px_t frame_get(px_t* buf, u16 x, u16 y) {
	return buf[x + y * SMALL_WIDTH];
}
