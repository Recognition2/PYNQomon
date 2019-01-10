#ifndef VIVADO_RECONFIGURABLE_FRAME_H
#define VIVADO_RECONFIGURABLE_FRAME_H

#include "app_config.hpp"
#include <stdint.h>

u8 compressRGB(u32 p);
void newFrame();


void frame_fill(u16 x, u16 y, u32 px);
//px_t frame_get(px_t* buf, u16 x, u16 y);
px_t frame_get(u16 idx, u16 px, bool doWrite);
u32 shitpixel(u16 x, u16 y);

u16 applyHamming(u16 newx, u16 newy, u8 px);
#endif
