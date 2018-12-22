#include "phase_correlation.hpp"
#include <stdint.h>
#include "app_config.hpp"
#include "frame.hpp"

void correlatiebeun(frame a, frame b, bool start, argmax* corrmax) {
	static const u16 centerX = SMALL_WIDTH / 2;
	static const u16 centerY = SMALL_HEIGHT / 2;
	static u16 i, j, m, n;
	static bool done;
	if (done) {
		return;
	}

	static u16 value;

	if (start) {
		i = 0;
		j = 0;
		m = SMALL_WIDTH;
		n = SMALL_WIDTH;
		done = false;
		argmax[0] = 0;
		argmax[1] = 0;
		value = 0;
	} else {
		n--;
		if (n == -1U) {
			n = SMALL_HEIGHT;
			m--;
			if (m == -1U) {
				m = SMALL_WIDTH;
				j++;
				if (j == SMALL_HEIGHT) {
					j = 0;
					i++;
					if (i == SMALL_WIDTH) {
						i = 0;
						// Done.
						done = true;
						return;
					}
				}
				value = 0;
			}
		}
	}

	const u16 jj = j + centerX - n;
	const u16 ii = i + centerY - m;
	if (ii < 0 || jj >= SMALL_WIDTH || jj < 0 || jj >= SMALL_HEIGHT) {
		return;
	}

	// r(i,j) = sum{m=1; M} sum{n=1; N} a(m,n)*b(m-i,n-j)
//	correlated[i][j] += frame_get(a, ii, jj) * frame_get(b, m, n);
	value += frame_get(a, ii, jj) * frame_get(b, m, n);
	if (value > corrmax->v) {
		corrmax->v = value;
		corrmax->x = i;
		corrmax->y = j;
	}

	// This takes SMALL_WIDTH^2 * SMALL_HEIGHT^2 iterations

//	for (u16 i = 0; i < SMALL_WIDTH; i++) {
//		for (u16 j = 0; j < SMALL_HEIGHT; j++) {
//			for (u16 m = SMALL_WIDTH - 1; m >= 0; m--) { // Flipped
//				for (u16 n = SMALL_HEIGHT; n >= 0; n--) { // FLipped
//					// Indices of input signal, check boundary pls
//
//
//					result[i][j] += frame_get(a, ii, jj) * frame_get(b, m, n);
//				}
//			}
//		}
//	}
}
