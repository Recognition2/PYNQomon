#include "buffer.hpp"
#include <stdint.h>

void newFrame(buffer *buf) {
	buf->which = (buf->which + 1) % FRAME_COUNT;
}

frame getFutureFrame(buffer *buf) {
	u8 which = (buf->which + 1) % FRAME_COUNT;
	return &buf->data[which * SMALL_HEIGHT * SMALL_WIDTH];
}

frame getCurrentFrame(buffer *buf) {
	return &buf->data[buf->which * SMALL_HEIGHT * SMALL_WIDTH];
}

frame getHistoryFrame(buffer *buf) {
	u8 which = (buf->which + FRAME_COUNT - 1) % FRAME_COUNT;
	return &buf->data[which * SMALL_HEIGHT * SMALL_WIDTH];
}

u8 compressRGB(u32 p) {
	u8 R = (p & 0xFF);
	u8 G = (p & 0xFF00) >> 8;
	u8 B = (p & 0xFF0000) >> 16;
	u8 A = (p & 0xFF000000) >> 24;

	return R >> 2 + R >> 5 	// 1/4 + 1/32
	+ G >> 1 + R >> 4		// 1/2 + 1/16
	+ B >> 3; // 1/8
}

void fill(buffer *buf, u16 x, u16 y, u32 p) {
	frame f = getFutureFrame(buf);

	// TODO: Translate x and y

	frame_fill(f, x, y, compressRGB(p));
}
