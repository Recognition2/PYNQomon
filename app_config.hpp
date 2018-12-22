#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdint.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint32_t u32;
typedef int32_t i32;

typedef struct {
	u16 x;
	u16 y;
	u16 v;
} argmax;

typedef struct {
	u16 x;
	u16 y;
} p16;

typedef ap_axiu<32, 1, 1, 1> pixel_data;
typedef hls::stream<pixel_data> pixel_stream;

#define WIDTH 1280
#define HEIGHT 720

#define SMALL_WIDTH 64
#define SMALL_HEIGHT 64

#define FRAME_COUNT 3

#define TRIAL_SIZE 2

extern u16 correlated[SMALL_WIDTH][SMALL_HEIGHT];

#endif
