#include "lag_pixel.h"

bool lag_init_color(lag_color *color, uchar r, uchar g, uchar b) {
	if (!color)
		return (false);
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = 255;
	return (true);
}

bool lag_init_pixel(lag_pixel *pixel, char *c, lag_color *bg, lag_color *fg) {
	if (!pixel)
		return (false);
	pixel->ch = c;
	if (bg) {
		pixel->bg = *bg;
		pixel->has_bg = true;
	} else {
		pixel->has_bg = false;
	}
	if (fg) {
		pixel->fg = *fg;
		pixel->has_fg = true;
	} else {
		pixel->has_fg = false;
	}
	return (true);
}

int	lag_pixel_to_str(char *dest, lag_pixel pixel) {
	int		offset = 0;
	char	*c = (pixel.ch) ? pixel.ch : " ";

	if (pixel.has_bg) {
		offset += sprintf(dest + offset, "\033[48;2;%d;%d;%dm", pixel.bg.r, pixel.bg.g, pixel.bg.b);
	}
	if (pixel.has_fg) {
		offset += sprintf(dest + offset, "\033[38;2;%d;%d;%dm", pixel.fg.r, pixel.fg.g, pixel.fg.b);
	}
	offset += sprintf(dest + offset, "%s\033[39;49m", c);
	return (offset);
}

bool	lag_show_pixel(lag_pixel pixel) {
	char	*c;
	if (pixel.has_bg) {
		printf("\033[48;2;%d;%d;%dm", pixel.bg.r, pixel.bg.g, pixel.bg.b);
	}
	if (pixel.has_fg) {
		printf("\033[38;2;%d;%d;%dm", pixel.fg.r, pixel.fg.g, pixel.fg.b);
	}
	c = (pixel.ch) ? pixel.ch : " ";
	printf("%s\033[39;49m", c);
	return (true);
}
