#include "frame.hpp"

#include "hammingcoefficients.h"
px_t applyHamming(u16 newx, u16 newy, px_t px) {
	u32 res = (u32) hamming[newx][newy] * (u32) px;
	return res >> 16;
}


void frame_fill(px_t* buf, u16 x, u16 y, px_t px) {

	const u32 newx = (x * SMALL_WIDTH) / WIDTH;
	const u32 newy = (y * SMALL_HEIGHT) / HEIGHT;

	px_t newpx = applyHamming(newx, newy, px);

	if( x % (WIDTH / SMALL_WIDTH) == 0 && y % (HEIGHT / SMALL_HEIGHT) == 0){
		buf[newx + newy * SMALL_WIDTH] = px;
	} else {
		buf[newx + newy * SMALL_WIDTH] += px;
	}

}

px_t frame_get(px_t* buf, u16 x, u16 y) {
	return buf[x + y * SMALL_WIDTH];
}
