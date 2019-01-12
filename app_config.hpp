#ifndef APP_CONFIG_H
#define APP_CONFIG_H
#ifndef __SYNTHESIS__
#include <stdio.h>
#include <hls_opencv.h>
//#include "opencv2/opencv.hpp"
#endif
#include <stdint.h>

#include <hls_video.h>
#include <hls_stream.h>
//#include <hls_opencv.h>
#include <ap_axi_sdata.h>

typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint64_t u64;

typedef struct {
	u64 v;
	i16 x;
	i16 y;
} maxCorrelationIndex;

typedef struct {
	u16 x;
	u16 y;
} Point;

typedef u16 Pixel;

// What's the type of a saved pixel?

typedef ap_axiu<32, 1, 1, 1> pixel_data;
typedef hls::stream<pixel_data> pixel_stream;

#define WIDTH 1280
#define HEIGHT 720

#define SMALL_WIDTH 80
#define SMALL_HEIGHT 45

#define FRAME_COUNT 3

extern u16 buf_which, buf_which_minus_one, buf_which_plus_one;
extern Pixel buf_data[FRAME_COUNT * SMALL_HEIGHT * SMALL_WIDTH];
//extern argmax corrmax;

#endif
