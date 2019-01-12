#include "app_config.hpp"
#include "buffer.hpp"
#include "phase_correlation.hpp"
#ifndef __SYNTHESIS__
#include <hls_stream.h>
#include <hls_opencv.h>
#include <stdio.h>
//#include "opencv2/opencv.hpp"
#endif

#include "pokemon.h"

u32 draw_pokemon(Point moved, u16 x, u16 y, u32 p) {
	const u32 magic_number = 0xFFcd5723;
	if ((x >= moved.x && x < moved.x + pokesize.x)
			&& (y >= moved.y && y < moved.y + pokesize.y)) {
		return (pokemon[x - moved.x][y - moved.y] != magic_number ?
				pokemon[x - moved.x][y - moved.y] : p);
	} else {
		return p;
	}
}

Pixel buf_data[FRAME_COUNT * SMALL_HEIGHT * SMALL_WIDTH];

void stream(pixel_stream &src, pixel_stream &dst, u32 mask) {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=&src
#pragma HLS INTERFACE axis port=&dst
#pragma HLS INTERFACE s_axilite port=mask
#pragma HLS PIPELINE II=1

	// Data to be stored across 'function calls'
	// Coordinates of current pixel
	static u16 x = 0;
	static u16 y = 0;

	// Frame selection
	static u16 currentFrame = 1;
	static u16 FutureFrame = 2;
	static u16 pastFrame = 0;

	static maxCorrelationIndex corrmax;

//	static u32 d;

	static Point moved = { WIDTH / 2, HEIGHT / 2 };
	static Point draw_moved = moved;
	u16 x_new = x;
	u16 y_new = y;
	pixel_data pIn;
	src >> pIn;
	static pixel_data pOut = pIn;

	const u32 pokedata = draw_pokemon(draw_moved, x_new, y_new, pIn.data);
	const u16 buf_which_old = currentFrame;
	const u16 buf_which_min_old = pastFrame;
	static maxCorrelationIndex corrmax_in_progress;
	// Only the last iteration;
	if (!pIn.user) {
		corrmax = corrmax_in_progress;

	}

	// Draw block
//	// Reset X and Y counters on user signal
	if (pIn.user) {
		// The only time that indices of max correlation are actually valid
		// Translate movement in small frame to movement in real frame
		if (corrmax.v != 0) {
			// Adjust coordinates of figure on screen
			const i16 xdiff = (corrmax.x - SMALL_WIDTH )* (WIDTH / SMALL_WIDTH);
			const i16 ydiff = (corrmax.y - SMALL_HEIGHT) * (HEIGHT / SMALL_HEIGHT);

			if (moved.x + xdiff + pokesize.x > WIDTH || moved.x + xdiff < 0) {
				moved.x = WIDTH / 2;
			} else {
				moved.x = xdiff + moved.x;
			}
			if (moved.y + ydiff + pokesize.y > HEIGHT || moved.y + ydiff < 0) {
				moved.y = HEIGHT / 2;
			} else {
				moved.y = ydiff + moved.y;
			}

#ifndef __SYNTHESIS__ // Simulation
			printf("moved is now {x: %d, y: %d}; diff is {%d %d, v: %llu}\n",
					moved.x, moved.y, xdiff, ydiff, corrmax.v);
#endif
		}
		// Reset X and Y
		x = y = 0;

		// Switch to a new frame
		newFrame(&currentFrame, &pastFrame);

		resetCorrelationData(&corrmax_in_progress);

		frame_fill(x, y, pIn.data, &FutureFrame, buf_which_old,true);

	} else if ((x + 1) % (WIDTH / SMALL_WIDTH) == 0
			&& (y + 1) % (HEIGHT / SMALL_HEIGHT) == 0) {

		frame_fill(x, y, pIn.data, &FutureFrame,  buf_which_old,true);

	} else {
		corrmax_in_progress = correlationStep(buf_which_old, buf_which_min_old, corrmax_in_progress);
		frame_fill(x, y, pIn.data, &FutureFrame, buf_which_old,false); // Do not allow store

	}

//
//	if (!(pIn.user || ((x + 1) % (WIDTH / SMALL_WIDTH) == 0
//					&& (y + 1) % (HEIGHT / SMALL_HEIGHT) == 0)))
//	{
//	}

	// add current pixel to the buffer

	// Perform one part of the correlation
	// Potentially draw figure at location `moved`
//	printf("hoi x %d y %d\n", x, y);

//	u32 durr = (shitpixel(x, y))|0xFF000000;
//	pIn.data = durr;

	////////////////////////////////
	///// END LOGIC

	pIn.data = pokedata;
	draw_moved = moved;
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

