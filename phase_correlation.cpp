#include "phase_correlation.hpp"
#include <stdint.h>
#include "app_config.hpp"
#include "frame.hpp"
#include "buffer.hpp"
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)

#define X SMALL_WIDTH
#define Y SMALL_HEIGHT
#define I_START_VALUE  ((X * 7) / 8)
#define I_END_VALUE    ((X * 9) / 8)
#define J_START_VALUE  ((Y * 7) / 8)
#define J_END_VALUE    ((Y * 9) / 8)
#define S_START_VALUE  (max(0, X-I_START_VALUE))
#define T_START_VALUE  (max(0, Y-J_START_VALUE))

static bool done = false;
static u64 value;
static i16 i = 0, j = 0;
static i16 s = 0, t = 0;
void resetCorrelationData() {
	done = false;
	corrmax.x = 0;
	corrmax.y = 0;
	corrmax.v = 0;
	value = 0;
	i = I_START_VALUE;
	j = J_START_VALUE;
	s = S_START_VALUE;
	t = T_START_VALUE;
	return;
}
/**
 * @param a the first frame to use in the correlation
 * @param b the second frame to use in the correlation
 * @param start whether this is the start of a new frame = new correlation calculation
 * @param corrmax is used for calculating the max of the correlation.
 */
void iterativeCorrelation(u16 x, u16 y) {
#pragma HLS inline
	if (done) {
		return;
	}

	const i16 idx_a_x = s - X + i;
	const i16 idx_a_y = t - Y + j;
	const i16 idx_b_x = s;
	const i16 idx_b_y = t;
//	const u16 aa = frame_get(getCurrentFrame(), idx_a_x, idx_a_y);
//	const u16 bb = frame_get(getHistoryFrame(), idx_b_x, idx_b_y);
	const u16 aa = frame_get(buf_which * SMALL_WIDTH * SMALL_HEIGHT + idx_a_x
					+ idx_a_y * SMALL_WIDTH, 0, false);
	const u16 buf_which_minus_one = (buf_which == 0 ? 2 : buf_which - 1);
	const u16 bb = frame_get(
			buf_which_minus_one * SMALL_WIDTH * SMALL_HEIGHT + idx_a_x
					+ idx_a_y * SMALL_WIDTH, 0, false);
	const u32 added = (aa * bb) >> 16;

//	printf("Trying to perform calculations\n");
	if (i < I_END_VALUE) { // x
		if (j < J_END_VALUE) { // y
			if (s < min(X-1, 2 * X - i-1)) {
				if (t < min(Y-1, 2 * Y - j-1)) {
#ifndef __SYNTHESIS__

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
				t = T_START_VALUE;
//				printf("t zero\n");
				s++;
				return;
			}
			s = S_START_VALUE;
			if (value > corrmax.v) {
				corrmax.v = value;
				corrmax.x = i;
				corrmax.y = j;
			}
#ifndef __SYNTHESIS__
//			printf("At point {%d, %d} the correlation is %d\n",i,j,value);
#endif
			value = 0;

			j++;
//			printf("s zero\n");
			return;
		}
//		printf("j = 0\n");
		j = J_START_VALUE;
		i++;
		return;
	}
//	printf("i = 0\n");
	done = true;
}
	
