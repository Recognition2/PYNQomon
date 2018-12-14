
#include "buffer.hpp"

Buffer::Buffer() {
	which = true;
}

uint8_t Buffer::compressRGB(uint32_t p) {
	uint8_t R = (p & 0xFF);
	uint8_t G = (p & 0xFF00) >> 8;
	uint8_t B = (p & 0xFF0000) >> 16;
	uint8_t A = (p & 0xFF000000) >> 24;

	return R;
}

void Buffer::fill(uint16_t x, uint16_t y, uint32_t p) {
	const uint16_t new_x = x * this->x / full_frame_x;
	const uint16_t new_y = y * this->y / full_frame_y;

	static const uint16_t factor = full_frame_x / this->x;

	const uint8_t data = compressRGB(p);

	const uint8_t new_data = data / factor;

	auto future = getFutureFrame();
	future[new_x + this->x * new_y] = new_data;
}

void Buffer::newFrame() {
	which = (which + 1) % FRAME_COUNT;
}

uint8_t* Buffer::getFutureFrame() {
	return &buf[(which + 1) % FRAME_COUNT];
}

uint8_t* Buffer::getCurrentFrame() {
	return &buf[which];
}

uint8_t* Buffer::getHistoryFrame() {
	return &buf[(which+FRAME_COUNT-1) % FRAME_COUNT];
}

