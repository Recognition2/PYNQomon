#include "app_config.hpp"
#include "buffer.hpp"
#include "phase_correlation.hpp"
#ifndef __SYNTHESIS__
#include <hls_stream.h>
#include <hls_opencv.h>
#include <stdio.h>
#endif

#include "pokemon.h"
#include "matti.h"
#include "mattirat1.h"
#include "mattirat2.h"


u32 draw_pokemon(Point moved, u16 x, u16 y, u32 p, u8 select_pokeface) {
	const u32 magic_number = 0xFFcd5723;
	if ((x >= moved.x && x < moved.x + pokesize.x)
			&& (y >= moved.y && y < moved.y + pokesize.y)) {
		Point point = {x - moved.x, y-moved.y};
		u32 getpokemon = pokemon[point.x][point.y];
		u32 getmatti = matti[point.x][point.y];
		u32 getmattirat1 = mattirat1[point.x][point.y];
		u32 getmattirat2 = mattirat2[point.x][point.y];

		u32 res = 0;
		switch (select_pokeface) {
		case POKEMON: 	res = getpokemon; break;
		case MATTI: 	res = getmatti; break;
		case MATTIRAT1: res = getmattirat1; break;
		case MATTIRAT2: res = getmattirat2; break;
		default: res = 0;
		}
		return (res != magic_number ? res : p);
	} else {
		return p;
	}
}

Pixel framebuffer[FRAME_COUNT * SMALL_HEIGHT * SMALL_WIDTH];

void stream(pixel_stream &src, pixel_stream &dst, u32 mask) {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=&src
#pragma HLS INTERFACE axis port=&dst
#pragma HLS INTERFACE s_axilite port=mask
#pragma HLS PIPELINE II=1

	const bool outputVideo = mask & (1<<0);
	const bool writeFigure = mask & (1<<1);
	const bool useDownscaled = (mask & (1<<2)); // Ignored as of yet, is an `ifdef`
	const bool doSnake = (mask & (1<<3));
	const u8 snakecontrols[SNAKE_COUNT] = {((mask>>SNAKE_P1) & 0x3), ((mask>>SNAKE_P2) & 0x3)};
	const u8 snake_every_n_frames = (mask>>24) & 0xFF;
	const u8 select_pokeface = (mask >> 5) & 0x3;
	const u8 select_filter = (mask>>12) & 0x7;


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

	const u32 pokedata = draw_pokemon(draw_moved, x_new, y_new, pIn.data, select_pokeface);
	const u16 buf_which_old = currentFrame;
	const u16 buf_which_min_old = pastFrame;
	static maxCorrelationIndex corrmax_in_progress;
	// Only the last iteration;

	static u8 old_snakecontrols[SNAKE_COUNT];
	const u32 snakecolor = run_snake_machine(snakecontrols, pIn.user,x,y,draw_moved, snake_every_n_frames);

	const Point resized = {x - (WIDTH/2 - SMALL_WIDTH/2), y - (HEIGHT/2 - SMALL_HEIGHT/2)};
	// Draw block
//	// Reset X and Y counters on user signal
	if (pIn.user) {
#ifndef __SYNTHESIS__
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
#endif
		// The only time that indices of max correlation are actually valid
		// Translate movement in small frame to movement in real frame
		if (corrmax.v != 0) {
			// Adjust coordinates of figure on screen
#ifdef DO_DOWNSAMPLE
			const i16 xdiff = (corrmax.x - SMALL_WIDTH )* (WIDTH / SMALL_WIDTH);
			const i16 ydiff = (corrmax.y - SMALL_HEIGHT) * (HEIGHT / SMALL_HEIGHT);
#else
			const i16 xdiff = (corrmax.x - SMALL_WIDTH );
			const i16 ydiff = (corrmax.y - SMALL_HEIGHT);
#endif


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
			printf("New Pokemon location is now {x: %d, y: %d}; diff is {%d %d, v: %llu}\n",
					moved.x, moved.y, xdiff, ydiff, corrmax.v);
#endif
		}
		// Reset X and Y
		x = y = 0;

		// Switch to a new frame
		newFrame(&currentFrame, &pastFrame);

		resetCorrelationData(&corrmax_in_progress);

		frame_fill(x, y, pIn.data, &FutureFrame, buf_which_old,true, select_filter);

#ifdef DO_DOWNSAMPLE
	} else if ((x + 1) % (WIDTH / SMALL_WIDTH) == 0
			&& (y + 1) % (HEIGHT / SMALL_HEIGHT) == 0) {
#else
	} else if (resized.x < SMALL_WIDTH && resized.y < SMALL_HEIGHT) {
#endif
		frame_fill(x, y, pIn.data, &FutureFrame,  buf_which_old,true, select_filter);
		corrmax = corrmax_in_progress;

	} else {
		corrmax_in_progress = correlationStep(buf_which_old, buf_which_min_old, corrmax_in_progress);
		frame_fill(x, y, pIn.data, &FutureFrame, buf_which_old,false, select_filter); // Do not allow store

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

	if (writeFigure) {
		if (doSnake) {
			pIn.data = (snakecolor == 0) ? pokedata : snakecolor;
		} else {
			pIn.data = pokedata;
		}
	}
	if (!outputVideo) {
		pIn.data = 0;
	}
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

