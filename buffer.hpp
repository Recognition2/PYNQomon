#ifndef VIVADO_RECONFIGURABLE_BUFFER_H
#define VIVADO_RECONFIGURABLE_BUFFER_H

#include "app_config.hpp"

#include <stdint.h>
#include "frame.hpp"

typedef struct {
	u16 which;
	u8 data[FRAME_COUNT * SMALL_HEIGHT * SMALL_WIDTH];
} buffer;

void newFrame(buffer *buf);

frame getFutureFrame(buffer *buf);
frame getCurrentFrame(buffer *buf);
frame getHistoryFrame(buffer *buf);
void fill(buffer *buf, u16 x, u16 y, u32 p);

#endif
