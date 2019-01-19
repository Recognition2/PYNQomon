#ifndef VIVADO_RECONFIGURABLE_FRAME_H
#define VIVADO_RECONFIGURABLE_FRAME_H

#include "app_config.hpp"

u16 applyFilter(u16 newx, u16 newy, u8 px);
u8 compressRGB(u32 p);
void newFrame(u16 *bufwhich, u16*buf_which_minus_one);

void frame_fill(u16 x, u16 y,u32 px,u16* futureFrame, u16 bufwhich,bool);
Pixel framebuffer_interact(u16 idx, u16 px, bool doWrite);

#endif
