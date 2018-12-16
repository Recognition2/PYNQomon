#ifndef VIVADO_RECONFIGURABLE_FRAME_H
#define VIVADO_RECONFIGURABLE_FRAME_H

#include "app_config.hpp"
#include <stdint.h>

class Frame {
	uint8_t buf[SMALL_HEIGHT*SMALL_WIDTH];

public:
	static const uint16_t x = SMALL_WIDTH, y=SMALL_HEIGHT;
	uint8_t rollx, rolly;

	Frame();
	
	void fill(uint16_t x, uint16_t y, uint8_t px);
	uint8_t const get(uint16_t x, uint16_t y);
	void setRoll(uint8_t x, uint8_t y);
};



#endif
