#include "phase_correlation.hpp"
#include <stdint.h>
#include "app_config.hpp"
#include "frame.hpp"

#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)

/**
 * @param a the first frame to use in the correlation
 * @param b the second frame to use in the correlation
 * @param start whether this is the start of a new frame = new correlation calculation
 * @param corrmax is used for calculating the max of the correlation.
 */
void iterativeCorrelation(px_t* a, px_t* b, bool start, argmax* corrmax) {
	static bool done = false;
	static u64 value;
	static i16 i = 0, j = 0;
	static i16 s = 0, t = 0;
	static const i32 X = SMALL_WIDTH;
	static const i32 Y = SMALL_HEIGHT;
	const i16 j_start_value = (Y + Y - 1) * 7 / 8;
	if (start) {
		done = false;
		corrmax->v = 0;
		value = 0;
		i = (X + X - 1) * 7 / 8;
		j = j_start_value;
		s = 0;
		t = 0;
	}
	if (done) {
		return;
	}

//	printf("Trying to perform calculations\n");
	if (i < (X + X - 1) * 3 / 4) { // x
		if (j < (Y + Y - 1) * 3 / 4) { // y
			if (s < min(X, 2 * X - i)) {
				if (t < min(Y, 2 * Y - j)) {
					const i16 idx_a_x = s - X + i - 1;
					const i16 idx_a_y = t - Y + j - 1;
					const i16 idx_b_x = s;
					const i16 idx_b_y = t;

//					if (idx_a_x >= 0 && idx_a_x < X && idx_a_y >= 0
//							&& idx_a_y < Y && idx_b_x >= 0 && idx_b_x < X
//							&& idx_b_y >= 0 && idx_b_y < Y) {

					value += frame_get(a, idx_a_x, idx_a_y)
							* frame_get(b, idx_b_x, idx_b_y);

//					}
					t++;
					return;
				}
				t = max(0, Y - j);
				s++;
				return;
			}
			s = max(0, X - i);
			if (value > corrmax->v) {
				corrmax->v = value;
				corrmax->x = i;
				corrmax->y = j;
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
	
