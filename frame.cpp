#include "frame.hpp"
#include "app_config.hpp"
#include "hammingcoefficients.h"
#include "hammingcoefficients_sqrt.h"
#include "hammingcoefficients_blackman.h"
#include "hammingcoefficients_bohman.h"
#include "hammingcoefficients_nuttall.h"
#include "hammingcoefficients_parzen.h"
#include "hammingcoefficients_tukey.h"

// Apply a filter to the current (downscaled) pixel
u16 applyFilter(u16 newx, u16 newy, u8 px, u8 select_filter) {
	const u16 fNone = 0xFFFF;
	const u16 fHamm = filter_hamming[newx][newy];
	const u16 fHSqr = filter_hamming_sqrt[newx][newy];
	const u16 fBlac = filter_blackman[newx][newy];
	const u16 fBohm = filter_bohman[newx][newy];
	const u16 fNutt = filter_nuttall[newx][newy];
	const u16 fParz = filter_parzen[newx][newy];
	const u16 fTuke = filter_tukey[newx][newy];

	u16 filterVal;
	switch (select_filter) {
	case None: 			filterVal = fNone; break;
	case Hamming:		filterVal = fHamm; break;
	case HammingSqrt:	filterVal = fHSqr; break;
	case Blackman:		filterVal = fBlac; break;
	case Bohman:		filterVal = fBohm; break;
	case Nuttall:		filterVal = fNutt; break;
	case Parzen:		filterVal = fParz; break;
	case Tukey:			filterVal = fTuke; break;
	default: filterVal = 0;
	}


	// 24 bits result, only allowed to return the last byte
	u32 res = (u32) filterVal * (u32) (px);
	if (res > (0xFF0000)) {
		printf("Number returned by `applyHamming` is too large to fit in the allocated space (0xFF0000) \n");
	}
#ifdef DO_DOWNSAMPLE
	return (res >>16) & 0xFFFF;
#else
	return (res >>8) & 0xFFFF;
#endif
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

// Provide one or the other implementation
#ifdef DO_DOWNSAMPLE
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
void frame_fill(u16 x, u16 y, u32 px, u16*futureFrame, u16 currentFrame, bool storeAllowed,u8 select_filter) {
#pragma HLS inline // must be inlined
	static Pixel px_store_buf[SMALL_WIDTH];
#pragma HLS array_partition variable=px_store_buf complete

	static u16 newx = 0;
	static u16 newy = 0;

//	const Pixel newpx = compressRGB(px);
	const Pixel newpx = (Pixel) applyFilter(newx,newy,compressRGB(px), select_filter);
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
			framebuffer_interact(idx, apparaat, true);
		}
	}
	*futureFrame = (currentFrame >= 2 ? 0 : currentFrame + 1);

	idx = *futureFrame * SMALL_WIDTH * SMALL_HEIGHT + newx	+ newy * SMALL_WIDTH;

	newx = (((x == WIDTH-1) ? 0 : x+1)* SMALL_WIDTH) / WIDTH;
	if (x == WIDTH-1) {
		newy = ((y == HEIGHT-1) ? 0 : y+1) * SMALL_HEIGHT / HEIGHT;
	}
}

// other implementation
#else
void frame_fill(u16 x, u16 y, u32 px, u16* futureFrame, u16 currentFrame, bool storeAllowed, u8 select_filter) {
#pragma HLS inline // must be inlined

	const Point resized = {x - (WIDTH/2 - SMALL_WIDTH/2), y - (HEIGHT/2 - SMALL_HEIGHT/2)};

//	const Pixel newpx = compressRGB(px);
	static u16 idx = 0;

	if (resized.x < SMALL_WIDTH && resized.y < SMALL_HEIGHT) {
		const Pixel newpx = (Pixel) applyFilter(resized.x,resized.y,compressRGB(px), select_filter);
		if (storeAllowed) {
			framebuffer[resized.x + resized.y * SMALL_WIDTH + *futureFrame * SMALL_WIDTH * SMALL_HEIGHT] = newpx;
		}
	}
	*futureFrame = (currentFrame >= 2 ? 0 : currentFrame + 1);


}
#endif

// Greyscale
u8 compressRGB(u32 p) {
	u8 B = (p & 0xFF); // Blue, checked
	u8 G = (p & 0xFF00) >> 8; // Green, checked
	u8 R = (p & 0xFF0000) >> 16;// Red, checked
	u8 A = (p & 0xFF000000) >> 24; // Alpha channel, checked
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

// This function is necessary because otherwise HLS complains.
// I'm sorry.
Pixel framebuffer_interact(u16 idx, u16 px, bool doWrite) {
//#pragma HLS inline off
//#pragma HLS function_instantiate variable=doWrite
	if (doWrite) {
		framebuffer[idx] = px;
		return 0;
	} else {
		return framebuffer[idx];
	}
}
