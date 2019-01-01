#ifndef APP_CONFIG_H
#define APP_CONFIG_H
//#include <stdio.h>
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
} argmax;

typedef struct {
	u16 x;
	u16 y;
} p16;

typedef u16 px_t;

// What's the type of a saved pixel?

typedef ap_axiu<32, 1, 1, 1> pixel_data;
typedef hls::stream<pixel_data> pixel_stream;

#define WIDTH 1280
#define HEIGHT 720

#define SMALL_WIDTH 128
#define SMALL_HEIGHT 72

#define FRAME_COUNT 3

#endif
