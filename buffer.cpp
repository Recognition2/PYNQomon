
#include "buffer.hpp"

Buffer::Buffer(): which(0) {
	for (int i = 0; i < FRAME_COUNT; i++) {
		frames[i] = new Frame();
	}
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

	static const uint16_t factor =
			full_frame_x * full_frame_y
			/ this->x / this->y;
	// Amount of pixels that appear in 1 px in the smaller version

	const uint8_t data = compressRGB(p);

	const uint8_t new_data = data / factor;

	Frame *future = getFutureFrame();
	future->fill(new_x, new_y, new_data);
}

void Buffer::newFrame() {
	which = (which + 1) % FRAME_COUNT;
}

Frame* const Buffer::getFutureFrame() {
	return frames[(which + 1) % FRAME_COUNT];
}

Frame* const Buffer::getCurrentFrame() {
	return frames[which];
}

Frame* const Buffer::getHistoryFrame() {
	return frames[(which+FRAME_COUNT-1) % FRAME_COUNT];
}

