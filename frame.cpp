
#include "frame.hpp"

Frame::Frame(uint16_t x, uint16_t y) {
	this->x = x;
	this->y = y;
	roll(0,0);

	uint8_t buf[x*y];
	this->buf = buf;
}

void Frame::fill(uint16_t x, uint16_t y, uint8_t px) {
	const auto newx = (x + rollx) % this->x;
	const auto newy = (y + rolly) % this->y;

	buf[newx + newy*this->x] = px;
}

uint8_t const Frame::get(uint16_t x, uint16_t y) {
	const auto newx = (x + rollx) % this->x;
	const auto newy = (y + rolly) % this->y;

	return buf[newx + newy*this->x];
}
void Frame::roll(uint8_t x, uint8_t y) {
	rollx = x;
	rolly = y;
}
