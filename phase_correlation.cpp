#include "phase_correlation.hpp"
#include <stdint.h>
#include "app_config.hpp"
#include "frame.hpp"

/**
 * @param a the first frame to use in the correlation
 * @param b the second frame to use in the correlation
 * @param start whether this is the start of a new frame = new correlation calculation
 * @param corrmax is used for calculating the max of the correlation.
 */
void iterativeCorrelation(px_t* a, px_t* b, bool start, argmax* corrmax) {
	static bool done = false;
	static u64 value;
	static i16 i, j;
	static i16 s, t;
	if (start) {
		done = false;
		corrmax->v = 0;
		value = 0;
		i = 0;
		j = 0;
		s = 0;
		t = 0;
	}
	if (done) {
		return;
	}

	static const u64 X = SMALL_WIDTH;
	static const u64 Y = SMALL_HEIGHT;
//	printf("Trying to perform calculations\n");
	if (i < X + Y - 1) { // x
		if (j < X + Y - 1) { // y
			s = 0;
			value = 0;
			while (s < 2 * X) {
				t = 0;
				while (t < 2 * Y) {
					i16 idx_a_x = s - X + i - 1;
					i16 idx_a_y = t - Y + j - 1;
					i16 idx_b_x = s;
					i16 idx_b_y = t;

					if (idx_a_x >= 0 && idx_a_x < X && idx_a_y >= 0
							&& idx_a_y < Y && idx_b_x >= 0 && idx_b_x < X
							&& idx_b_y >= 0 && idx_b_y < Y) {

						value += frame_get(a, idx_a_x, idx_a_y)
								* frame_get(b, idx_b_x, idx_b_y);

					}
					t++;
				}
				s++;
			}
			if (value > corrmax->v) {
				corrmax->v = value;
				corrmax->x = i;
				corrmax->y = j;
				}
			j++;
//			printf("s,t zero\n");
			return;
		}
//		printf("j = 0\n");
		j = 0;
		i++;
		return;
	}
//	printf("i = 0\n");
	i = 0;
	done = true;
}
	
