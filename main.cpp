#include "app_config.hpp"
#include "buffer.hpp"
#include "convolution.hpp"
#include "phase_correlation.hpp"

//u16 correlated[SMALL_WIDTH][SMALL_HEIGHT];

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

	static p16 moved = { 0, 0 };

	static buffer buf;

	pixel_data pIn;
	src >> pIn;
	static pixel_data pOut = pIn;
	static argmax corr;

	// Load pixel data from source

//	// Reset X and Y counters on user signal
	if (pIn.user) {
		// The only time that `corr` is actually valid
		moved.x += corr.x;
		moved.y += corr.y;

		x = y = 0;
		newFrame(&buf);
		fill(&buf, x, y, pIn.data);

		// Takes a very long time
//		int16_t* indices = get_correct_offset(buffer.getCurrentFrame(), buffer.getHistoryFrame());
	}

	// Every iteration:
	correlatiebeun(getCurrentFrame(&buf), getHistoryFrame(&buf), pIn.user,
			&corr);
	correlatiebeun(getCurrentFrame(&buf), getHistoryFrame(&buf), pIn.user,
			&corr);

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

