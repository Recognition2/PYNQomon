#ifndef VIVADO_RECONFIGURABLE_FRAME_H
#define VIVADO_RECONFIGURABLE_FRAME_H

#include "app_config.hpp"
#include <stdint.h>

void frame_fill(px_t* buf, u16 x, u16 y, px_t px);
px_t frame_get(px_t* buf, u16 x, u16 y);

#endif
