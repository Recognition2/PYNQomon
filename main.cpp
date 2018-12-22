#include "app_config.hpp"
#include "buffer.hpp"
#include "convolution.hpp"
#include "phase_correlation.hpp"
#define SIM
#ifdef SIM
#include "stdio.h"
#endif

//u16 correlated[SMALL_WIDTH][SMALL_HEIGHT];
bool is_within(x_u16 x_now, p16 target, u16 n) {
return (current.x >= target.x && current.x < target.x + 50) &&;
}

u32 draw_pokemon(p16 *moved, u16 x, u16 y, u32 p) {
	const p16 pokesize = { 64, 64 };

	if (moved->x + pokesize.x > WIDTH) {
		moved->x = WIDTH / 2;
	}
	if (moved->y + pokesize.y > HEIGHT) {
		moved->y = HEIGHT / 2;
	}

	if ((x >= moved->x && x < moved->x + 50)
		&& (y >= moved->y && y < moved->y + 50)) {
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
	static argmax corr;

	// Load pixel data from source

	// Reset X and Y counters on user signal
	if (pIn.user) {
		// The only time that `corr` is actually valid
		moved.x += corr.x - SMALL_WIDTH / 2;
		moved.y += corr.y - SMALL_HEIGHT / 2;

		x = y = 0;
		newFrame(&buf);
		fill(&buf, x, y, pIn.data);

	}

	// Every iteration:
	for (u8 i = 0; i < 19; i++) {
		correlatiebeun(getCurrentFrame(&buf), getHistoryFrame(&buf), pIn.user,
				&corr);
	}

	// needs to happen 19 times because 19 is the first number for which
	// 1280 * 720 * N > SMALL_WIDTH^2 * SMALL_HEIGHT^2


	pIn.data = draw_pokemon(&moved, x, y, pIn.data);
#ifdef SIM
	printf("%u %u %ul\n", corr.x, corr.y, corr.v);
#endif
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

