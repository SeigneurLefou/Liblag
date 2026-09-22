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

bool lag_set_pixel(lag_pixel *pixel, const char *c, lag_color *fg, lag_color *bg) {
	if (!pixel)
		return false;
	memset(pixel, 0, sizeof(lag_pixel));
	if (c && *c) {
		strncpy(pixel->ch, c, sizeof(pixel->ch) - 1);
	} else {
		pixel->ch[0] = ' ';
		pixel->ch[1] = '\0';
	}
	if (fg) {
		pixel->fg = *fg;
		pixel->has_fg = true;
	}
	if (bg) {
		pixel->bg = *bg;
		pixel->has_bg = true;
	}
	return true;
}

int lag_get_pixel_size(const lag_pixel *pixel) {
	if (!pixel)
		return 0;

	int size = 0;
	const char *c = (pixel->ch[0]) ? pixel->ch : " ";

	if (pixel->has_bg)
		size += snprintf(NULL, 0, "\033[48;2;%u;%u;%um", pixel->bg.r, pixel->bg.g, pixel->bg.b);
	if (pixel->has_fg)
		size += snprintf(NULL, 0, "\033[38;2;%u;%u;%um", pixel->fg.r, pixel->fg.g, pixel->fg.b);

	size += strlen(c);
	size += strlen("\033[39;49m");
	return size;
}

bool lag_pixel_to_str(const lag_pixel *pixel, char *out_buf, size_t max_len) {
	if (!pixel || !out_buf) return false;
	
	int offset = 0;
	const char *c = (pixel->ch[0]) ? pixel->ch : " ";

	if (pixel->has_bg) {
		offset += snprintf(out_buf + offset, max_len - offset, 
						   "\033[48;2;%u;%u;%um", pixel->bg.r, pixel->bg.g, pixel->bg.b);
	}
	if (pixel->has_fg) {
		offset += snprintf(out_buf + offset, max_len - offset, 
						   "\033[38;2;%u;%u;%um", pixel->fg.r, pixel->fg.g, pixel->fg.b);
	}
	snprintf(out_buf + offset, max_len - offset, "%s\033[39;49m", c);
	return true;
}
