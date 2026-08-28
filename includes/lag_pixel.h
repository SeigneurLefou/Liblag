#ifndef LAG_PIXEL_H
#define LAG_PIXEL_H

#include "lag_utils.h"

typedef struct	s_lag_color {
	short	r;
	short	g;
	short	b;
}	lag_color;

typedef struct	s_lag_pixel {
    char ch;
    short color_pair;
}	lag_pixel;

bool	lag_init_color(short r, short g, short b);
bool	lag_init_pixel(lag_pixel *pixel, char c, lag_color bg, lag_color fg);

#endif
