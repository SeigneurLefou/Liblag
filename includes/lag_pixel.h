#ifndef LAG_PIXEL_H
# define LAG_PIXEL_H

# include "lag_utils.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_lag_color {
	uchar	r;
	uchar	g;
	uchar	b;
	uchar	a;
}	lag_color;

typedef struct s_lag_pixel {
	char		ch[8];
	lag_color	fg;
	lag_color	bg;
	bool		has_fg;
	bool		has_bg;
}	lag_pixel;

bool	lag_set_color(lag_color *color, uchar r, uchar g, uchar b);
bool	lag_set_pixel(lag_pixel *pixel, const char *c, lag_color *fg, lag_color *bg);
bool	lag_pixel_to_str(const lag_pixel *pixel, char *out_buf, size_t max_len);
int		lag_get_pixel_size(const lag_pixel *pixel);
bool	lag_show_pixel(lag_pixel pixel);

#endif
