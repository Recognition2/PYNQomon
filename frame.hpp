#ifndef VIVADO_RECONFIGURABLE_FRAME_H
#define VIVADO_RECONFIGURABLE_FRAME_H

#include "app_config.hpp"
#include <stdint.h>

px_t compressRGB(u32 p);
void newFrame();


void frame_fill(u16 x, u16 y, px_t px);
//px_t frame_get(px_t* buf, u16 x, u16 y);

#endif
