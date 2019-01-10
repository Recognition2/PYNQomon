#include "phase_correlation.hpp"
#include <stdint.h>
#include "app_config.hpp"
#include "frame.hpp"
#include "buffer.hpp"

#define custom_max(a,b) \
   ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define custom_min(a,b) \
   ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#ifndef __SYNTHESIS__
using namespace cv;
#endif

#define X SMALL_WIDTH
#define Y SMALL_HEIGHT
#define I_START_VALUE  ((X * 7) / 8)
#define I_END_VALUE    ((X * 9) / 8)
#define J_START_VALUE  ((Y * 7) / 8)
#define J_END_VALUE    ((Y * 9) / 8)
//#define S_START_VALUE  (custom_max(0, X-i))
//#define T_START_VALUE  (custom_max(0, Y-j))

static bool done = false;
static u64 value;
static i16 i = 0, j = 0;
static i16 s = 0, t = 0;

inline i16 get_s_start_value() {
	return custom_max(0,X-i);
}

inline i16 get_t_start_value() {
	return custom_max(0,Y-j);
}

void resetCorrelationData() {
	done = false;
	corrmax.x = 0;
	corrmax.y = 0;
	corrmax.v = 0;
	value = 0;
	i = I_START_VALUE;
	j = J_START_VALUE;
	s = get_s_start_value();
	t = get_t_start_value();
	return;
}

/**
 * @param a the first frame to use in the correlation
 * @param b the second frame to use in the correlation
 * @param start whether this is the start of a new frame = new correlation calculation
 * @param corrmax is used for calculating the max of the correlation.
 */
void correlationStep(u16 /*unused*/, u16 /*unused*/) {
//#pragma HLS inline
#pragma HLS inline off
	if (done) {
		return;
	}

	const i16 idx_a_x = s;
	const i16 idx_a_y = t;
	const i16 idx_b_x = s - X + i;
	const i16 idx_b_y = t - Y + j;
	const i32 frame_idx_a = buf_which * SMALL_WIDTH * SMALL_HEIGHT + idx_a_x + idx_a_y * SMALL_WIDTH;
	const i16 buf_which_minus_one = (buf_which == 0 ? 2 : buf_which - 1);

	const i32 frame_idx_b = buf_which_minus_one * SMALL_WIDTH * SMALL_HEIGHT + idx_b_x + idx_b_y * SMALL_WIDTH;
//	const u32 aa = frame_get(frame_idx_a, 0, false);
//	const u32 bb = frame_get(frame_idx_b, 0, false);
	const u32 aa = buf_data[frame_idx_a];
	const u32 bb = buf_data[frame_idx_b];
	const u64 added = (aa * bb);
#ifndef __SYNTHESIS__
	static u8 correlatieVisualisatie[I_END_VALUE - I_START_VALUE + 1][J_END_VALUE - J_START_VALUE +1] {};
#endif
//	printf("Trying to perform calculations\n");
	if (i <= I_END_VALUE) { // x
		if (j <= J_END_VALUE) { // y
			if (s <= custom_min(X-1, 2 * X - i-1)) {
				if (t <= custom_min(Y-1, 2 * Y - j-1)) {
#ifndef __SYNTHESIS__
					if (value + added < value) {
						printf("Value plus the new sum gives a smaller result than expected., went wrong in the correlation\n");
					}
					if (idx_a_x >= 0 && idx_a_x < X && idx_a_y >= 0
							&& idx_a_y < Y && idx_b_x >= 0 && idx_b_x < X
							&& idx_b_y >= 0 && idx_b_y < Y) {
#endif
						value += (u64) added;
#ifndef __SYNTHESIS__
					} else {
						printf("ILLEGAL memory access at i: %d, j: %d, s: %d, t: %d\n",i,j,s,t);
						printf("Indices: a {%d,%d} b {%d,%d}\n", idx_a_x,idx_a_y,idx_b_x,idx_b_y);
					}
#endif
					t++;
					return;
				}
				t = get_t_start_value();
//				printf("t zero\n");
				s++;
				return;
			}

			s = get_s_start_value();
			t = get_t_start_value();
#ifndef __SYNTHESIS__
//			if (value == corrmax.v) {
//				printf("Two equal correlation values, this cannot be correct.\n");
//			}
#endif
			if (value > corrmax.v) {
				corrmax.v = value;
				corrmax.x = i;
				corrmax.y = j;
			}
#ifndef __SYNTHESIS__
			const int shft_amt = 34;
			if ((value>>shft_amt) > 0xFF) {
				printf("De correlatie is wel heel erg groot, wel groter dan FF\n");
			}
			correlatieVisualisatie[i - I_START_VALUE][j-J_START_VALUE] = (value>>shft_amt) & 0xFF;
			if (i == SMALL_WIDTH - 1 && j == SMALL_HEIGHT - 1) {
				printf("De midden is de beste beest %lld\n", value);
			}
//			printf("At point {%d, %d} the correlation is %d\n",i,j,value);
#endif
			value = 0;

			j++;
//			printf("s zero\n");
			return;
		}
//		printf("j = 0\n");
		j = J_START_VALUE;
		s = get_s_start_value();
		t = get_t_start_value();
		i++;
		return;
	}
//	printf("i = 0\n");
#ifndef __SYNTHESIS__
	static u32 counter = 0;
	char buf[100];
	counter++;
	printf("Het einde van een freem is bereikt\n");
	cv::Mat m;
	m = cv::Mat(cv::Size(J_END_VALUE - J_START_VALUE + 1, I_END_VALUE - I_START_VALUE + 1), CV_8UC1, (void*)correlatieVisualisatie);
	cv::resize(m, m, cv::Size(480,640));
	sprintf(buf,"/tmp/resultaten/correlatiefoto_%d.jpg",counter);
	cv::imwrite(buf, m);

#endif
	done = true;
}
	
