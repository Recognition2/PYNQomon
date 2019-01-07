#include "frame.hpp"

#include "hammingcoefficients.h"
px_t applyHamming(u16 newx, u16 newy, px_t px) {
	u32 res = hamming[newx][newy] * px;
	return res >> 16;
}


void frame_fill(u16 x, u16 y, px_t px) {
#pragma HLS inline
	static px_t buffertje[SMALL_WIDTH];
#pragma HLS dependence variable=buffertje intra false
//#pragma HLS array_partition variable=buffertje complete

	const u16 newx = (x * SMALL_WIDTH) / WIDTH;
	const u16 newy = (y * SMALL_HEIGHT) / HEIGHT;

	px_t newpx = applyHamming(newx, newy, px);
	const u16 buf_which_new = (buf_which + 1) == 3 ? 0 : buf_which + 1;
	const u16 idx = buf_which_new * SMALL_WIDTH * SMALL_HEIGHT + newx
			+ newy * SMALL_WIDTH;
	const u16 beest = buffertje[newx] + px;

	if( x % (WIDTH / SMALL_WIDTH) == 0 && y % (HEIGHT / SMALL_HEIGHT) == 0){
		buffertje[newx] = px;
	} else if ((x + 1) % (WIDTH / SMALL_WIDTH) == 0
			&& (y + 1) % (HEIGHT / SMALL_HEIGHT) == 0) {
		frame_get(idx, beest, true);
	} else {
		buffertje[newx] = beest;
	}

//	if( x % (WIDTH / SMALL_WIDTH) == 0 && y % (HEIGHT / SMALL_HEIGHT) == 0){
//		buf_data[idx] = px;
//	} else {
//		buf_data[idx] += px;
//	}

}

void newFrame() {
	u16 a;
	switch (buf_which) {
	case 0:
		a = 1;
		break;
	case 1:
		a = 2;
		break;
	case 2:
		a = 0;
	}
	buf_which = a;
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

px_t frame_get(u16 idx, u16 px, bool doWrite) {
//#pragma HLS inline off
	if (doWrite) {
		buf_data[idx] = px;
		return 0;
	} else {
		return buf_data[idx];
	}
}

