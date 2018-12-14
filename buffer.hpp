#ifndef VIVADO_RECONFIGURABLE_BUFFER_H
#define VIVADO_RECONFIGURABLE_BUFFER_H


#include <stdint.h>


class Buffer {
public:
	static const int full_frame_x = 1280;
	static const int full_frame_y = 720;
	static const int x = 64;
	static const int y = 32;
	static const int FRAME_COUNT = 4;
	
	uint8_t buf[FRAME_COUNT][x*y];
	uint8_t which;

	Buffer();
	void newFrame();
	
	void fill(uint16_t x,uint16_t y, uint32_t rgba);

	uint8_t* getFutureFrame();
	uint8_t* getCurrentFrame();
	uint8_t* getHistoryFrame();

private:
	uint8_t compressRGB(uint32_t p);
};



#endif
