#ifndef VIVADO_RECONFIGURABLE_FRAME_H
#define VIVADO_RECONFIGURABLE_FRAME_H

#include "app_config.hpp"
#include <stdint.h>

typedef struct {
	u16 x;
	u16 y;
} Roll;

typedef u8* frame;

void frame_fill(frame buf, u16 x, u16 y, u8 px);
u8 frame_get(frame buf, u16 x, u16 y);

#endif
