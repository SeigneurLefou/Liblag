#ifndef LAG_PIXEL_H
# define LAG_PIXEL_H

# include "lag_utils.h"
# include <stdbool.h>
# include <stdio.h>

typedef struct s_lag_color {
	uchar	r;
	uchar	g;
	uchar	b;
	uchar	a;
}	lag_color;

typedef struct s_lag_pixel {
	char		ch;
	lag_color	fg;
	lag_color	bg;
	bool		has_fg;
	bool		has_bg;
}	lag_pixel;

bool lag_init_color(lag_color *color, uchar r, uchar g, uchar b);
bool lag_init_pixel(lag_pixel *pixel, char c, lag_color *bg, lag_color *fg);
bool lag_show_pixel(lag_pixel pixel);

#endif
