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

/**
 * @param x: Current x coordinate in the large frame
 * @param y: Current y coordinate in the large frame
 * @param futureFrame: index in the `data` buffer for the frame-to-fill
 * @param currentFrame: index in the `data` buffer of one of the frames currently being correlated
 * @param storeAllowed: Useless parameter, only used to 'allow a store on the global array'
 * 						However, the behaviour was correct anyway. The parameter is necessary because otherwise
 * 						Vivado HLS cannot make assumptions that hold
 *
 */
void frame_fill(u16 x, u16 y, u32 px, u16*futureFrame, u16 currentFrame, bool storeAllowed) {
#pragma HLS inline // must be inlined
	static Pixel px_store_buf[SMALL_WIDTH];
#pragma HLS array_partition variable=px_store_buf complete

	static u16 newx = 0;
	static u16 newy = 0;

//	const px_t newpx = compressRGB(px);
	const Pixel newpx = (Pixel) applyHamming(newx,newy,compressRGB(px));
	const u16 bufRead = px_store_buf[newx];
	const Pixel apparaat = bufRead + newpx;
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
	} else if (is_end_frame) {
#ifndef __SYNTHESIS__
		if (idx > ((*futureFrame+1) * SMALL_WIDTH * SMALL_HEIGHT)) {
			printf("De index van het getal wat we gaan fillen is onmogelijk groot\n");
			printf("buf_which+1 = %d, idx=%d\n", *futureFrame,idx);
		}
#endif
		if (storeAllowed) {
			frame_get(idx, apparaat, true);
		}
	}
	*futureFrame = (currentFrame >= 2 ? 0 : currentFrame + 1);

	idx = *futureFrame * SMALL_WIDTH * SMALL_HEIGHT + newx	+ newy * SMALL_WIDTH;

	newx = (((x == WIDTH-1) ? 0 : x+1)* SMALL_WIDTH) / WIDTH;
	if (x == WIDTH-1) {
		newy = ((y == HEIGHT-1) ? 0 : y+1) * SMALL_HEIGHT / HEIGHT;
	}
}

void newFrame(u16 *currentFrame, u16 *pastFrame) {
	u16 tmp;
	switch (*currentFrame) {
	case 0:
		tmp = 1;
		break;
	case 1:
		tmp = 2;
		break;
	case 2:
		tmp = 0;
	}
	*pastFrame = *currentFrame;
	*currentFrame = tmp;
}

// Greyscale
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

Pixel frame_get(u16 idx, u16 px, bool doWrite) {
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
