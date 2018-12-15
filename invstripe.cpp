#include <stdint.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

#include "buffer.hpp"

typedef ap_axiu<32,1,1,1> pixel_data;
typedef hls::stream<pixel_data> pixel_stream;

#define WIDTH 1280
#define HEIGHT 720

void stream(pixel_stream &src, pixel_stream &dst, uint32_t mask)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=&src
#pragma HLS INTERFACE axis port=&dst
#pragma HLS INTERFACE s_axilite port=mask
#pragma HLS PIPELINE II=1

	// Data to be stored across 'function calls'
	static uint16_t x = 0;
	static uint16_t y = 0;
	static uint32_t d;

	static Buffer buffer;

//	static uint8_t rowbuf[WIDTH] = {};
//	static uint8_t colbuf[HEIGHT] = {};
//
//	static uint8_t rowbuf_hist[WIDTH];
//	static uint8_t colbuf_hist[HEIGHT];

	pixel_data pIn;
	src >> pIn;
	static pixel_data pOut = pIn;

	// Load pixel data from source

//	// Reset X and Y counters on user signal
	if (pIn.user) {
		x = y = 0;
		buffer.newFrame();
		unsigned char meuk[2];
//		// do analysis once a frame
//
//		// Setup history for next frame
//		for (int i = 0; i < WIDTH; i++) {
//			rowbuf_hist[i] = rowbuf[i];
//		}
//		for (int i = 0; i < HEIGHT; i++) {
//			colbuf_hist[i] = colbuf[i];
//		}
	}

	/// START LOGIC
	////////////////////////////////

//	// Decompose mask input
//	bool invert = (mask&1)>0;
//
//	if (x > WIDTH/2+50 && invert) {
//		pIn.data = ~(pIn.data & 0x00FFFFFF) | (pIn.data & 0xFF000000); // invert only the RGB channels
//	}
//	if (x == WIDTH/2) {
//		colbuf[y] = toGrey(pIn.data);
//	}
//	if (y == HEIGHT/2) {
//		rowbuf[x] = toGrey(pIn.data);
//	}

//	// Make greyfilter
	uint8_t grey = toGrey(pIn.data);
	uint32_t goeiemorgen= grey | (grey << 8) | (grey << 16) | 0xFF000000;
	pIn.data = goeiemorgen;



	////////////////////////////////
	///// END LOGIC

	// Write pixel to destination
	dst << pOut;
	pOut = pIn;

	// Increment X and Y counters
	if (pIn.last)
	{
		x = 0;
		y++;
	}
	else
		x++;
}

