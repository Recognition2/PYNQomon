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
	static bool done;
	if (done) {
		return;
	}

	static u64 value;

	if (start) {
		done = false;
		corrmax->v = 0;
		value = 0;
	}

	static const u64 X = SMALL_WIDTH;
	static const u64 Y = SMALL_HEIGHT;

	static u8 i = 0;
	while (i < X + Y - 1) { // x
		static u8 j = 0;
		while (j < X + Y - 1) { // y
			value = 0;
			static i16 s = 0;
			while (s < 2 * X) {
				static i16 t = 0;
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
				return;
			}
			if (value > corrmax->v) {
				corrmax->v = value;
				corrmax->x = i;
				corrmax->y = j;
				}
			j++;
			return;
		}
		i++;
		return;
	}
	done = true;
}
	
