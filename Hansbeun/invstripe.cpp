#include <stdint.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<32,1,1,1> pixel_data;
typedef hls::stream<pixel_data> pixel_stream;

#define WIDTH 1280
#define HEIGHT 720
#define WINDOW_WIDTH 50
#define WINDOW_HEIGHT 50

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

	//Data to be stored across 'function calls'
	static uint16_t x = 0;
	static uint16_t y = 0;
	static uint32_t d;
	
	//Initialize window coordinates
	static uint8_t wx = 0;
	static uint8_t wy = 0;

	//Windows
	static uint8_t window[WINDOW_WIDTH][WINDOW_HEIGHT] = {};
	static uint8_t window_hist[WINDOW_WIDTH][WINDOW_HEIGHT] = {};
	
	//Define pixels
	pixel_data pIn, pOut;

	// Load pixel data from source
	src >> pIn;


	// Reset X and Y counters on user signal and setup history for next frame
	if (pIn.user) {
		x = y = 0;
		for (int i = 0; i < WIDTH; i++) {
			for(int j = 0; j < HEIGHT; j++) {
				window_hist[i][j] = window[i][j];
			}			
		}
		
	}

	/// START LOGIC
	////////////////////////////////

	//Store grey value if pixel is within window in center of screen
	if (x > (WIDTH - WINDOW_WIDTH) / 2 && x < (WIDTH + WINDOW_WIDTH) / 2) {
		wx = x - ((WIDTH - WINDOW_WIDTH) / 2);
		if (y > (HEIGHT - WINDOW_HEIGHT) / 2 && y < (HEIGHT - WINDOW_HEIGHT) / 2) {
			wy = y - ((HEIGHT - WINDOW_HEIGHT) / 2);
			window[wx][wy] = toGrey(pIn.data);
		}
	}


	// Decompose mask input
	/*bool invert = (mask&1)>0;

	if (x > WIDTH/2+50 && invert) {
		pIn.data = ~(pIn.data & 0x00FFFFFF) | (pIn.data & 0xFF000000); // invert only the RGB channels
	}*/

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

