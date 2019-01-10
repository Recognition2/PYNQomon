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

u32 draw_pokemon(p16 moved, u16 x, u16 y, u32 p) {
	const u32 magic_number = 0xFF2357cd;
	if ((x >= moved.x && x < moved.x + pokesize.x)
			&& (y >= moved.y && y < moved.y + pokesize.y)) {
		return (pokemon[x - moved.x][y - moved.y] != magic_number ?
				pokemon[x - moved.x][y - moved.y] : p);
	} else {
		return p;
	}
}

argmax corrmax;

u16 buf_which, buf_which_plus_one, buf_which_minus_one;
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
//	static u32 d;

	static p16 moved = { WIDTH / 2, HEIGHT / 2 };

	pixel_data pIn;
	src >> pIn;
	static pixel_data pOut = pIn;

	const u32 pokedata = draw_pokemon(moved, x, y, pIn.data);
	const u16 buf_which_old = buf_which;

	// Draw block
#pragma HLS dependence variable=corrmax intra false
#pragma HLS dependence variable=corrmax inter false
	// Reset X and Y counters on user signal
#pragma HLS dependence variable=buf_data inter false
#pragma HLS dependence variable=buf_data intra false
#pragma HLS dependence variable=moved inter false
#pragma HLS dependence variable=moved intra false
#pragma HLS dependence variable=buf_which intra false
#pragma HLS dependence variable=buf_which inter false
#pragma HLS dependence variable=buf_which_minus_one intra false
#pragma HLS dependence variable=buf_which_minus_one inter false
	if (pIn.user) {
		// The only time that `corr` is actually valid
		// Translate movement in small frame to movement in real frame
//		if (corrmax.v != 0) {
			const i16 xdiff = ((corrmax.x - SMALL_WIDTH )* WIDTH) / SMALL_WIDTH;
			const i16 ydiff = ((corrmax.y - SMALL_HEIGHT) * HEIGHT)	/ SMALL_HEIGHT;

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

#ifndef __SYNTHESIS__
			{
				cv::Mat intermediate;
				static int COUNTER = 0;
				printf("moved is now {x: %d, y: %d}; diff is {%d %d, v: %llu}\n",
						moved.x,
						moved.y, xdiff, ydiff, corrmax.v);
				char buffer[100];
				sprintf(buffer, "/tmp/resultaten/intermediate_afbeelding_hist_%d.jpg\0",COUNTER);
	//			cv::resize(buf_data[buf_which * SMALL_WIDTH * SMALL_HEIGHT], intermediate, cv::Size(0,0), 16, 16, cv::INTER_NEAREST);
	//			cv::cvtColor(intermediate, intermediate, CV_GRAY2RGBA);
	//		    cv::Mat imgCvOut(cv::Size(WIDTH, HEIGHT), CV_8UC4, buf_data[buf_which * SMALL_WIDTH * SMALL_HEIGHT]);
	//			cv::imwrite(buffer, intermediate);
	//			for (int i = 0; i < SMALL_HEIGHT * SMALL_WIDTH; i++) {
	//				sprintf(buffer, "%d ", buf_data[buf_which * SMALL_HEIGHT * SMALL_WIDTH + i]);
	//			}
			}
#endif
//		}

		x = y = 0;

		newFrame();
		resetCorrelationData();

	} else if ((x + 1) % (WIDTH / SMALL_WIDTH) == 0
			&& (y + 1) % (HEIGHT / SMALL_HEIGHT) == 0) {
		correlationStep(buf_which_old);

	}

	frame_fill(x, y, pIn.data);
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

