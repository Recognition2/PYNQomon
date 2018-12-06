#include <stdint.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<32,1,1,1> pixel_data;
typedef hls::stream<pixel_data> pixel_stream;

#define WIDTH 1280
#define HEIGHT 720

uint8_t toGrey(uint32_t p) {
	uint8_t R = (p & 0xFF);
	uint8_t G = (p & 0xFF00) >> 8;
	uint8_t B = (p & 0xFF0000) >> 16;
	return  R >> 2 + R >> 5 	// 1/4 + 1/32
		+	G >> 1 + R >> 4		// 1/2 + 1/16
		+	B >> 3;				// 1/8
}



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

//	static uint8_t rowbuf[WIDTH] = {};
//	static uint8_t colbuf[HEIGHT] = {};
//
//	static uint8_t rowbuf_hist[WIDTH];
//	static uint8_t colbuf_hist[HEIGHT];

	pixel_data pIn, pOut;

	// Load pixel data from source
	src >> pIn;

//	// Reset X and Y counters on user signal
//	if (pIn.user) {
//		x = y = 0;
//		// do analysis once a frame
//
//		// Setup history for next frame
//		for (int i = 0; i < WIDTH; i++) {
//			rowbuf_hist[i] = rowbuf[i];
//		}
//		for (int i = 0; i < HEIGHT; i++) {
//			colbuf_hist[i] = colbuf[i];
//		}
//	}

	/// START LOGIC
	////////////////////////////////

	// Decompose mask input
	bool invert = (mask&1)>0;

	if (x > WIDTH/2+50 && invert) {
		pIn.data = ~(pIn.data & 0x00FFFFFF) | (pIn.data & 0xFF000000); // invert only the RGB channels
	}
//
//	if (x == WIDTH/2) {
//		colbuf[y] = toGrey(pIn.data);
//	}
//	if (y == HEIGHT/2) {
//		rowbuf[x] = toGrey(pIn.data);
//	}

//	// Make greyfilter
//	uint8_t grey = toGrey(pIn.data);
//	uint32_t goeiemorgen= grey | (grey << 8) | (grey << 16)|(pIn.data & 0xFF000000);
//	pOut.data = goeiemorgen;

	pOut = pIn;


	////////////////////////////////
	///// END LOGIC

	// Write pixel to destination
	dst << pOut;

	// Increment X and Y counters
	if (pIn	.last)
	{
		x = 0;
		y++;
	}
	else
		x++;
}

