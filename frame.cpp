#include "frame.hpp"

void frame_fill(frame buf, u16 x, u16 y, u8 px) {
	buf[x + y * SMALL_WIDTH] = px;
}

u8 frame_get(frame buf, u16 x, u16 y) {
	return buf[x + y * SMALL_WIDTH];
}
