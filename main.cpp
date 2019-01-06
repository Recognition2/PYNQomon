#include "app_config.hpp"
#include "buffer.hpp"
#include "convolution.hpp"
#include "phase_correlation.hpp"
#ifndef __SYNTHESIS__
#include "stdio.h"
#endif

u32 draw_pokemon(p16 *moved, u16 x, u16 y, u32 p) {
	const p16 pokesize = { 64, 64 };

	if (moved->x + pokesize.x > WIDTH) {
		moved->x = WIDTH / 2;
	}
	if (moved->y + pokesize.y > HEIGHT) {
		moved->y = HEIGHT / 2;
	}

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


void stream(pixel_stream &src, pixel_stream &dst, u32 mask) {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=&src
#pragma HLS INTERFACE axis port=&dst
#pragma HLS INTERFACE s_axilite port=mask
#pragma HLS PIPELINE II=1

	// Data to be stored across 'function calls'
	static u16 x = 0;
	static u16 y = 0;
	static u32 d;

	static p16 moved = { WIDTH / 2, HEIGHT / 2 };

	static buffer buf;

	pixel_data pIn;
	src >> pIn;
	static pixel_data pOut = pIn;
	static argmax corr = { 0, 0, 0 };

	// Draw block
	pIn.data = draw_pokemon(&moved, x, y, pIn.data);

	// Reset X and Y counters on user signal
	if (pIn.user) {
		// The only time that `corr` is actually valid
		// Translate movement in small frame to movement in real frame
		if (corr.v != 0) {
			moved.x += (corr.x - (SMALL_WIDTH / 2));
			//* WIDTH) / SMALL_WIDTH;
			moved.y += (corr.y - (SMALL_HEIGHT / 2));
			//* HEIGHT) / SMALL_HEIGHT;
		}
		//moved.x += 1;
		//moved.y += 0;
#ifndef __SYNTHESIS__
		printf("moved is now {x: %d, y: %d}; corr is {%d %d, v: %llu}\n",
				moved.x,
				moved.y, corr.x, corr.y, corr.v);
#endif


		x = y = 0;
//		for (int i = 0; i < SMALL_HEIGHT; i++) {
//			for (int j = 0; j < SMALL_WIDTH; j++) {
//				printf("%03d ", frame_get(getFutureFrame(&buf), j, i));
//			}
//			printf("\n");
//		}

		newFrame(&buf);
	}

	// Perform one part of the correlation
	iterativeCorrelation(getCurrentFrame(&buf), getHistoryFrame(&buf), pIn.user,
			&corr);

	// add current pixel to the relevant pixel buffer
	frame_fill(getFutureFrame(&buf), x, y, pIn.data);




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

