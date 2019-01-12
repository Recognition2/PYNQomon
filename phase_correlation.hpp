#ifndef VIVADO_RECONFIGURABLE_PHASECORRELATION_H
#define VIVADO_RECONFIGURABLE_PHASECORRELATION_H

#include "frame.hpp"
void resetCorrelationData(maxCorrelationIndex *corrmax);
maxCorrelationIndex correlationStep(u16 buf_which,u16, maxCorrelationIndex);

#endif
