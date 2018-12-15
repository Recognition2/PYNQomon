#ifndef VIVADO_RECONFIGURABLE_FRAME_H
#define VIVADO_RECONFIGURABLE_FRAME_H


#include <stdint.h>


class Frame {
	uint8_t *buf;
	const uint16_t x,y;
	uint8_t rollx, rolly;
public:
	Frame(uint16_t x, uint16_t y);
	
	void fill(uint16_t x, uint16_t y, uint8_t px);
	uint8_t const get(uint16_t x, uint16_t y);
	void roll(uint8_t x, uint8_t y);
};



#endif
