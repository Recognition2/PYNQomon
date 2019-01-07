#include "app_config.hpp"
#include "buffer.hpp"
#include "convolution.hpp"
#include "phase_correlation.hpp"
#ifndef __SYNTHESIS__
#include "stdio.h"
#endif

const p16 pokesize = { 64, 64 };

u32 draw_pokemon(p16 *moved, u16 x, u16 y, u32 p) {
	if ((x >= moved->x && x < moved->x + pokesize.x)
			&& (y >= moved->y && y < moved->y + pokesize.y)) {
		if ((x >= moved->x + 10 && x < moved->x + 40)
				&& (y >= moved->y + 10 && y < moved->y + 40)) {
			return (p & 0xFF000000) | 0x000000; // Black filling
		} else {
			return (p & 0xFF000000) | 0xFFFFFF; // With white border
		}
	} else {
		return p;
	}
}

argmax corrmax;

u16 buf_which;
px_t buf_data[FRAME_COUNT * SMALL_HEIGHT * SMALL_WIDTH];


void stream(pixel_stream &src, pixel_stream &dst, u32 mask) {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=&src
#pragma HLS INTERFACE axis port=&dst
#pragma HLS INTERFACE s_axilite port=mask
#pragma HLS PIPELINE II=1

#pragma HLS array_partition variable=buf_data block factor=3
	// Data to be stored across 'function calls'
	static u16 x = 0;
	static u16 y = 0;
	static u32 d;

	static p16 moved = { WIDTH / 2, HEIGHT / 2 };

	pixel_data pIn;
	src >> pIn;
	static pixel_data pOut = pIn;

	// Draw block
#pragma HLS dependence variable=corrmax intra false
#pragma HLS dependence variable=corrmax inter false
	// Reset X and Y counters on user signal
#pragma HLS dependence variable=buf_data inter false
#pragma HLS dependence variable=buf_data intra false
#pragma HLS dependence variable=buf_which intra false
#pragma HLS dependence variable=buf_which inter false
	if (pIn.user) {
		// The only time that `corr` is actually valid
		// Translate movement in small frame to movement in real frame
		if (corrmax.v != 0) {
			const u16 xdiff = (corrmax.x - (SMALL_WIDTH / 2));
			//* WIDTH) / SMALL_WIDTH;
			const u16 ydiff = (corrmax.y - (SMALL_HEIGHT / 2));
			//* HEIGHT) / SMALL_HEIGHT;

			if (moved.x + xdiff + pokesize.x > WIDTH) {
				moved.x = WIDTH / 2;
			} else {
				moved.x = xdiff + moved.x;
			}
			if (moved.y + ydiff + pokesize.y > HEIGHT) {
				moved.y = HEIGHT / 2;
			} else {
				moved.y = ydiff + moved.y;
			}

		}

		//moved.x += 1;
		//moved.y += 0;
#ifndef __SYNTHESIS__
		printf("moved is now {x: %d, y: %d}; corr is {%d %d, v: %llu}\n",
				moved.x,
				moved.y, corrmax.x, corrmax.y, corrmax.v);
#endif

		x = y = 0;

		newFrame();
		resetCorrelationData();

	} else {
		iterativeCorrelation();
	}
	// add current pixel to the buffer

	frame_fill(x, y, pIn.data);

	// Perform one part of the correlation
	// Potentially draw figure at location `moved`
	pIn.data = draw_pokemon(&moved, x, y, pIn.data);


//	//pIn.data = draw_pokemon(&moved, x, y, pIn.data);
//	u32 durr = (shitpixel(&buf , x, y))|0xFF000000;
//	//printf("%03d ", durr);
//
//	pIn.data = durr;
	//printf("%u %u %lu\n", corr.x, corr.y, corr.v);
	////////////////////////////////
	///// END LOGIC


	// Write pixel to destination
	dst << pOut;
	pOut = pIn;

	// Increment X and Y counters
	if (pIn.last) {
		x = 0;
		y++;
	} else {
		x++;
	}
}

