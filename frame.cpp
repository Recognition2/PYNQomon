#include "frame.hpp"
#include "app_config.hpp"
#include "hammingcoefficients.h"


u16 applyHamming(u16 newx, u16 newy, u8 px) {
	// 24 bits result, only allowed to return the last byte
	u32 res = (u32) (hamming[newx][newy]) * (u32) (px);
	if (res > (0xFF0000)) {
		printf("Number returned by `applyHamming` is too large to fit in the allocated space (0xFF0000) \n");
	}
	return (res >>16) & 0xFFFF;
}

void frame_fill(u16 x, u16 y, u32 px, u16*buf_which_plus_one, u16 buf_which, bool storeAllowed) {
#pragma HLS inline
	static px_t px_store_buf[SMALL_WIDTH];
#pragma HLS array_partition variable=px_store_buf complete

	static u16 newx = 0;
	static u16 newy = 0;

//	const px_t newpx = compressRGB(px);
	const px_t newpx = (px_t) applyHamming(newx,newy,compressRGB(px));
	const u16 bufRead = px_store_buf[newx];
	const px_t apparaat = bufRead + newpx;
#ifndef __SYNTHESIS__
	if (apparaat < bufRead) {
		printf("number added by `frame_fill` is overflowing!\n");
	}
#endif
	static u16 idx = 0;
	const bool is_start_frame = x % (WIDTH / SMALL_WIDTH) == 0 && y % (HEIGHT / SMALL_HEIGHT) == 0;
	const bool is_end_frame = (x + 1) % (WIDTH / SMALL_WIDTH) == 0
			&& (y + 1) % (HEIGHT / SMALL_HEIGHT) == 0;

	px_store_buf[newx] = (is_end_frame) ? 0 : apparaat;
	if( is_start_frame){
//		buffertje[newx] = newpx;
//		px_store_buf[newx] = newpx;
//#ifndef __SYNTHESIS__
//		printf("Reset buffertjes\n");
//#endif
	} else if ((x + 1) % (WIDTH / SMALL_WIDTH) == 0
			&& (y + 1) % (HEIGHT / SMALL_HEIGHT) == 0) {
#ifndef __SYNTHESIS__
		if (idx > ((*buf_which_plus_one+1) * SMALL_WIDTH * SMALL_HEIGHT)) {
			printf("De index van het getal wat we gaan fillen is onmogelijk groot\n");
			printf("buf_which+1 = %d, idx=%d\n", *buf_which_plus_one,idx);
		}
#endif
		if (storeAllowed) {
			frame_get(idx, apparaat, true);
		}
//		px_store_buf[newx] = 0;
//#ifndef __SYNTHESIS__
//		printf("Assign buffertjes\n");
//#endif
	} else {
//		px_store_buf[newx] = apparaat;
//#ifndef __SYNTHESIS__
//		printf("Iter\n");
//#endif
	}
	*buf_which_plus_one = (buf_which >= 2 ? 0 : buf_which + 1);

//	if( x % (WIDTH / SMALL_WIDTH) == 0 && y % (HEIGHT / SMALL_HEIGHT) == 0){
//		buf_data[idx] = px;
//	} else {
//		buf_data[idx] += px;
//	}
	idx = *buf_which_plus_one * SMALL_WIDTH * SMALL_HEIGHT + newx	+ newy * SMALL_WIDTH;

	newx = (((x == WIDTH-1) ? 0 : x+1)* SMALL_WIDTH) / WIDTH;
	if (x == WIDTH-1) {
		newy = ((y == HEIGHT-1) ? 0 : y+1) * SMALL_HEIGHT / HEIGHT;
	}
}

void newFrame(u16 *buf_which, u16 *buf_which_minus_one) {

//#pragma HLS dependence variable=buf_which inter false
//#pragma HLS dependence variable=buf_which intra false

	u16 a;
//#pragma HLS dependence variable=a inter false
//#pragma HLS dependence variable=a intra false
	switch (*buf_which) {
	case 0:
		a = 1;
		break;
	case 1:
		a = 2;
		break;
	case 2:
		a = 0;
	}
	*buf_which_minus_one = *buf_which;
	*buf_which = a;
}
u8 compressRGB(u32 p) {
	u8 B = (p & 0xFF);
	u8 G = (p & 0xFF00) >> 8;
	u8 R = (p & 0xFF0000) >> 16;// Red, certain
	u8 A = (p & 0xFF000000) >> 24; // ALpha channel, certain
	u32 res = (R>>2) + (R>>5) 	// 1/4 + 1/32
			+ (G>>1) + (G>>4)		// 1/2 + 1/16
			+ (B>>3); // 1/8

#ifndef __SYNTHESIS__
	if (res > 0xFF) {
		printf("Number returned by `compressRGB` is too large to fit\n");
	}

#endif
	return (u8) (res & 0xFF);
}

px_t frame_get(u16 idx, u16 px, bool doWrite) {
//#pragma HLS inline off
//#pragma HLS function_instantiate variable=doWrite
	if (doWrite) {
		buf_data[idx] = px;
		return 0;
	} else {
		return buf_data[idx];
	}
}
//u32 shitpixel(u16 x, u16 y){
//  const u32 newx = (x * SMALL_WIDTH) / WIDTH;
//  const u32 newy = (y * SMALL_HEIGHT) / HEIGHT;
//  px_t out = frame_get(buf_which * SMALL_WIDTH * SMALL_HEIGHT + newx + newy * SMALL_WIDTH, 0, false);
//  return (u32) (out >> 8) * 0x010101;
//}
