#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdint.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<32,1,1,1> pixel_data;
typedef hls::stream<pixel_data> pixel_stream;

#define WIDTH 1280
#define HEIGHT 720

#define SMALL_WIDTH 64
#define SMALL_HEIGHT 32

#endif
