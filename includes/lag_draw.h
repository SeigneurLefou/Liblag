#ifndef lag_DRAW_H
#define lag_DRAW_H

#include "lag_utils.h"
#include <stdbool.h>
#include "lag_buffer.h"

bool lag_draw_pixel(lag_buffer *buf, uint x, uint y, char c);

#endif
