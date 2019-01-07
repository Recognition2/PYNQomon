#include "buffer.hpp"
#include <stdint.h>


//
//px_t* getFutureFrame() {
//	u8 which = (buf_which + 1) % FRAME_COUNT;
//	return &buf_data[which * SMALL_HEIGHT * SMALL_WIDTH];
//}
//
//px_t* getCurrentFrame() {
//	return buf_data + 2 * buf_which * SMALL_HEIGHT * SMALL_WIDTH;
//}
//
//px_t* getHistoryFrame() {
//	u8 which = (buf_which + FRAME_COUNT - 1) % FRAME_COUNT;
//	return &buf_data[which * SMALL_HEIGHT * SMALL_WIDTH];
//}



//void fill(buffer *buf, u16 x, u16 y, u32 p) {
//	px_t* f = getFutureFrame(buf);
//
//	// TODO: Translate x and y
//	// And apply Hamming
//
//	frame_fill(f, x, y, compressRGB(p));
//}

//u32 shitpixel(buffer *buf, u16 x, u16 y){
//	const u32 newx = (x * SMALL_WIDTH) / WIDTH;
//	const u32 newy = (y * SMALL_HEIGHT) / HEIGHT;
//	px_t out = frame_get(getHistoryFrame(buf), newx, newy);
//	return (u32) out;
//}
