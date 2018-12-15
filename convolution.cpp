
#include "convolution.hpp"

uint8_t max_of_xcorr(uint8_t* current, uint8_t* hist) {
	
	static const int size = Buffer::x * Buffer::y;
	
	for (uint16_t i = 0; i < Buffer::x; i++) {
		for (uint16_t j = 0; j < Buffer::y; j++) {
			const auto corr =
		}
	}
	
}
