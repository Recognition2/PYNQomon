#ifndef VIVADO_RECONFIGURABLE_BUFFER_H
#define VIVADO_RECONFIGURABLE_BUFFER_H


#include <stdint.h>
#include "frame.hpp"

class Buffer {
public:
	static const int full_frame_x = 1280;
	static const int full_frame_y = 720;
	static const int x = 64, y=32;
	static const int FRAME_COUNT = 4;
	
	Buffer();
	void newFrame();
	
	void fill(uint16_t x,uint16_t y, uint32_t rgba);

	Frame* const getFutureFrame();
	Frame* const getCurrentFrame();
	Frame* const getHistoryFrame();

private:
	Frame frames[FRAME_COUNT];
	uint8_t which;
	uint8_t compressRGB(uint32_t p);
};



#endif
