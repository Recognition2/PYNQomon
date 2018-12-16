
#include "convolution.hpp"

#define abs(x) (res >= 0 ? res : -res)

#define CHECK_SIZE 4

int16_t* get_correct_offset(Frame* curr, Frame* hist) {
	static int16_t results[2];

	static const uint8_t trial_size = 2;

	uint32_t sumdiffs[trial_size*2][trial_size*2];

	for (int16_t i = -trial_size; i < trial_size; i++) {
		for (int16_t j = -trial_size; j < trial_size; j++) {
			sumdiffs[trial_size + i][trial_size + j] = sum_diff(curr,hist,i,j);
		}
	}

	// Get minimum value from array
	uint32_t min_value = -1;
	for (int16_t i = 0; i < trial_size*2; i++) {
		for (int16_t j = 0; j < trial_size*2; j++) {
			if (sumdiffs[i][j] < min_value) {
				// Save new indices
				results[0] = i - trial_size;
				results[j] = j - trial_size;
				// And value
				min_value = sumdiffs[i][j];
			}
		}
	}

	return results;
}

uint32_t sum_diff(Frame* curr, Frame* hist, uint16_t x, uint16_t y) {
	uint32_t sum = 0;
	
	hist->setRoll(0,0);
	curr->setRoll(x,y);

	for (uint8_t i = 0; i < curr->x; i++) {
		for (uint8_t j = 0; j < curr->y; j++) {
			if (i > curr->x - x || j > curr->y - y) {
				continue;
			}
			int32_t res = abs((int32_t) curr->get(i,j) - (int32_t) hist->get(i,j));
			sum += res;
		}
	}
	return sum;
}
