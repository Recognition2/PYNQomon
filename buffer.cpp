#include "buffer.hpp"
#include <stdint.h>

void newFrame(buffer *buf) {
	buf->which = (buf->which + 1) % FRAME_COUNT;
}

px_t* getFutureFrame(buffer *buf) {
	u8 which = (buf->which + 1) % FRAME_COUNT;
	return &buf->data[which * SMALL_HEIGHT * SMALL_WIDTH];
}

px_t* getCurrentFrame(buffer *buf) {
	return &buf->data[buf->which * SMALL_HEIGHT * SMALL_WIDTH];
}

px_t* getHistoryFrame(buffer *buf) {
	u8 which = (buf->which + FRAME_COUNT - 1) % FRAME_COUNT;
	return &buf->data[which * SMALL_HEIGHT * SMALL_WIDTH];
}

px_t compressRGB(u32 p) {
	u8 R = (p & 0xFF);
	u8 G = (p & 0xFF00) >> 8;
	u8 B = (p & 0xFF0000) >> 16;
	u8 A = (p & 0xFF000000) >> 24;

	return (px_t) G;
//	return R >> 2 + R >> 5 	// 1/4 + 1/32
//	+ G >> 1 + R >> 4		// 1/2 + 1/16
//	+ B >> 3; // 1/8
}

void fill(buffer *buf, u16 x, u16 y, u32 p) {
	px_t* f = getFutureFrame(buf);



	// TODO: Translate x and y
	// And apply Hamming


	frame_fill(f, x, y, compressRGB(p));
}

u32 shitpixel(buffer *buf, u16 x, u16 y){
	const u32 newx = (x * SMALL_WIDTH) / WIDTH;
	const u32 newy = (y * SMALL_HEIGHT) / HEIGHT;
	px_t out = frame_get(getHistoryFrame(buf), newx, newy);
	return (u32) out;



}
