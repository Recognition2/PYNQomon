#ifndef VIVADO_RECONFIGURABLE_CONVOLUTION_H
#define VIVADO_RECONFIGURABLE_CONVOLUTION_H

#include <stdint.h>

#include "buffer.hpp"

int16_t* get_correct_offset(Frame* curr, Frame* hist);

uint32_t sum_diff(Frame* curr, Frame* hist, uint16_t x, uint16_t y);


#endif
