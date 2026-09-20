#include "lag_pixel.h"

bool lag_set_color(lag_color *color, uchar r, uchar g, uchar b) {
	if (!color)
		return (false);
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = 255;
	return (true);
}

bool	lag_set_pixel(lag_pixel *pixel, char *c, lag_color *bg, lag_color *fg) {
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
	pixel->content = lag_pixel_to_str(pixel);
	return (true);
}

int lag_get_pixel_size(const lag_pixel *pixel) {
    if (!pixel)
        return 0;

    int size = 0;
    const char *c = (pixel->ch) ? pixel->ch : " ";

    if (pixel->has_bg)
        size += snprintf(NULL, 0, "\033[48;2;%u;%u;%um", pixel->bg.r, pixel->bg.g, pixel->bg.b);
    if (pixel->has_fg)
        size += snprintf(NULL, 0, "\033[38;2;%u;%u;%um", pixel->fg.r, pixel->fg.g, pixel->fg.b);

    size += strlen(c);
    size += strlen("\033[39;49m");
    return size;
}

char *lag_pixel_to_str(const lag_pixel *pixel) {
    if (!pixel)
        return NULL;

    int size = lag_get_pixel_size(pixel);
    char *res = malloc(size + 1);
    if (!res)
        return NULL;

    int offset = 0;
    const char *c = (pixel->ch) ? pixel->ch : " ";

    if (pixel->has_bg) {
        offset += sprintf(res + offset, "\033[48;2;%u;%u;%um",
                          pixel->bg.r, pixel->bg.g, pixel->bg.b);
    }
    if (pixel->has_fg) {
        offset += sprintf(res + offset, "\033[38;2;%u;%u;%um",
                          pixel->fg.r, pixel->fg.g, pixel->fg.b);
    }

    sprintf(res + offset, "%s\033[39;49m", c);
    return res;
}
