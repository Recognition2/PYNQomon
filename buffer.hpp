#ifndef VIVADO_RECONFIGURABLE_BUFFER_H
#define VIVADO_RECONFIGURABLE_BUFFER_H

#include "app_config.hpp"

#include <stdint.h>
#include "frame.hpp"

typedef struct {
	u16 which;
	u16 data[FRAME_COUNT * SMALL_HEIGHT * SMALL_WIDTH];
} buffer;

void newFrame(buffer *buf);

px_t* getFutureFrame(buffer *buf);
px_t* getCurrentFrame(buffer *buf);
px_t* getHistoryFrame(buffer *buf);
px_t compressRGB(u32 p);
void fill(buffer *buf, u16 x, u16 y, u32 p);
u32 shitpixel(buffer *buf, u16 x, u16 y);

#endif
