/**
 * app_config.hpp
 * Authors: Hans Okkerman & Kevin Hill
 * This file contains structures and variables needed throughout the whole program.
 */

#ifndef APP_CONFIG_H
#define APP_CONFIG_H

/**
 * Includes
 */
#ifndef __SYNTHESIS__ // Simulation
#include <stdio.h>
#include <hls_opencv.h>
#endif

#include <stdint.h>

#include <hls_video.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<32, 1, 1, 1> pixel_data;
typedef hls::stream<pixel_data> pixel_stream;

// Full-size resolution
#define WIDTH 1280
#define HEIGHT 720


// In what way do we save the buffer? By downsampling or by picking a square in the middle
#define DO_DOWNSAMPLE

// Amount of buffered frames
#define FRAME_COUNT 3

// Resolution of buffered frame
#define SMALL_WIDTH 80
#define SMALL_HEIGHT 45

/**
 * Typedefs for brevity
 * Borrowed from Rust
 */
typedef uint8_t  u8;
typedef int8_t   i8;
typedef uint16_t u16;
typedef int16_t  i16;
typedef uint32_t u32;
typedef int32_t  i32;
typedef uint64_t u64;

typedef struct {
	u16 x;
	u16 y;
} Point;

// Which window filter to use
enum Filters {
	None,
	Hamming,
	HammingSqrt,
	Blackman,
	Bohman,
	Nuttall,
	Parzen,
	Tukey,
};



// Size of a pixel in the low-res frame
typedef u16 Pixel;

// buf_which's are used for indexing framebuffer
extern u16 buf_which, buf_which_minus_one, buf_which_plus_one;

// Complete buffer for all pixels
extern Pixel framebuffer[FRAME_COUNT * SMALL_HEIGHT * SMALL_WIDTH];

// The correlation is calculated on a point-by-point basis. This struct stores
// the maximum of the correlation, and the corresponding coordinates
typedef struct {
	u64 v;
	i16 x;
	i16 y;
} maxCorrelationIndex;


// Pokemon drawing
extern const Point pokesize;
enum pokeSelect {
	POKEMON = 0,
	MATTI = 1,
	MATTIRAT1 = 2,
	MATTIRAT2 = 3,
};

// Snake
#define SNAKE_COUNT 2 // Amount of snakes

#define SNAKE_MAX_LENGTH 1024

#define SNAKE_P1 8  // Offset in the mask used for controls of snake 1
#define SNAKE_P2 10 // Similarly, snake 2
extern u32 run_snake_machine(const u8[2], bool reset,u16,u16,Point,u8);

// What direction is the snake
enum Direction {
	Right = 0,
	Down = 1,
	Left = 2,
	Up = 3,
};

typedef struct {
	u8 maxlen;
	Direction dir;
	u32 color;
	u8 len;
//	Point pos[SNAKE_MAX_LENGTH]; // While actually a part of a snake,
	// it has been moved to a separate array for HLS-synthesizability
} Snake;

/**
 * Useful macros
 */
#define custom_abs(x)\
   ({ __typeof__ (x) _x = (x); \
	  _x < 0 ? -_x : _x; })

#define custom_max(a,b) \
   ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define custom_min(a,b) \
   ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })


#endif
