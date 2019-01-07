#include "phase_correlation.hpp"
#include <stdint.h>
#include "app_config.hpp"
#include "frame.hpp"
#include "buffer.hpp"

#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)

#define X SMALL_WIDTH
#define Y SMALL_HEIGHT
#define i_start_value (((X + X - 1) * 7) / 8)
#define i_end_value   (((X + X - 1) * 9) / 8)
#define j_start_value (((Y + Y - 1) * 7) / 8)
#define j_end_value   (((Y + Y - 1) * 9) / 8)

static bool done = false;
static u64 value;
static i16 i = 0, j = 0;
static i16 s = 0, t = 0;
void resetCorrelationData() {
	done = false;
	corrmax.v = 0;
	value = 0;
	i = i_start_value;
	j = j_start_value;
	s = 0;
	t = 0;
	return;
}
/**
 * @param a the first frame to use in the correlation
 * @param b the second frame to use in the correlation
 * @param start whether this is the start of a new frame = new correlation calculation
 * @param corrmax is used for calculating the max of the correlation.
 */
void iterativeCorrelation() {
#pragma HLS inline
	if (done) {
		return;
	}

	const i16 idx_a_x = s - X + i - 1;
	const i16 idx_a_y = t - Y + j - 1;
	const i16 idx_b_x = s;
	const i16 idx_b_y = t;
//	const u16 aa = frame_get(getCurrentFrame(), idx_a_x, idx_a_y);
//	const u16 bb = frame_get(getHistoryFrame(), idx_b_x, idx_b_y);
	const u16 aa = buf_data[buf_which * SMALL_WIDTH * SMALL_HEIGHT + idx_a_x
			+ idx_a_y * SMALL_WIDTH];
	const u16 bb = buf_data[((buf_which + FRAME_COUNT - 1) % FRAME_COUNT)
			* SMALL_WIDTH * SMALL_HEIGHT + idx_a_x + idx_a_y * SMALL_WIDTH];
	const u32 added = (u32) aa * (u32) bb;

//	printf("Trying to perform calculations\n");
	if (i < i_end_value) { // x
		if (j < j_end_value) { // y
			if (s < min(X, 2 * X - i)) {
				if (t < min(Y, 2 * Y - j)) {
//					if (idx_a_x >= 0 && idx_a_x < X && idx_a_y >= 0
//							&& idx_a_y < Y && idx_b_x >= 0 && idx_b_x < X
//							&& idx_b_y >= 0 && idx_b_y < Y) {

					value += (u64) added;

//					}
					t++;
					return;
				}
				t = max(0, Y - j);
				s++;
				return;
			}
			s = max(0, X - i);
			if (value > corrmax.v) {
				corrmax.v = value;
				corrmax.x = i;
				corrmax.y = j;
			}
			value = 0;

			j++;
//			printf("s,t zero\n");
			return;
		}
//		printf("j = 0\n");
		j = j_start_value;
		i++;
		return;
	}
//	printf("i = 0\n");
	i = 0;
	done = true;
}
	
