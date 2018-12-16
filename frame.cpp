
#include "frame.hpp"

Frame::Frame() {
	setRoll(0,0);
}

void Frame::fill(uint16_t x, uint16_t y, uint8_t px) {
	const uint16_t newx = (x + rollx) % this->x;
	const uint16_t newy = (y + rolly) % this->y;

	buf[newx + newy*this->x] = px;
}

uint8_t const Frame::get(uint16_t x, uint16_t y) {
	const uint16_t newx = (x + this->x + rollx) % this->x;
	const uint16_t newy = (y + this->y + rolly) % this->y;

	return buf[newx + newy*this->x];
}
void Frame::setRoll(uint8_t x, uint8_t y) {
	rollx = x;
	rolly = y;
}
