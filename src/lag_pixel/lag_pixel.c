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

bool	lag_init_pixel(lag_pixel *pixel, char *c, lag_color *bg, lag_color *fg) {
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

int	lag_get_pixel_size(lag_pixel pixel) {
	int		size = 0;
	char	*c = (pixel.ch) ? pixel.ch : " ";

	if (pixel.has_bg) {
		size += strlen("\033[48;2;");
		size += strlen(sprintf("%d", pixel.bg.r));
		size += strlen(";");
		size += strlen(sprintf("%d", pixel.bg.g));
		size += strlen(";");
		size += strlen(sprintf("%d", pixel.bg.b));
		size += strlen("m");
	}
	if (pixel.has_fg) {
		size += strlen("\033[48;2;");
		size += strlen(sprintf("%d", pixel.fg.r));
		size += strlen(";");
		size += strlen(sprintf("%d", pixel.fg.g));
		size += strlen(";");
		size += strlen(sprintf("%d", pixel.fg.b));
		size += strlen("m");
	}
	size += strlen(c);
	size += strlen("\033[39;49m");
	return (size);
}

char	*lag_pixel_to_str(lag_pixel pixel) {
	char	*res = malloc(lag_get_pixel_size(pixel))
	char	*c = (pixel.ch) ? pixel.ch : " ";

	if (pixel.has_bg) {
		strcat(res, "\033[48;2;");
		strcat(res, sprintf("%d", pixel.bg.r));
		strcat(res, ";");
		strcat(res, sprintf("%d", pixel.bg.g));
		strcat(res, ";");
		strcat(res, sprintf("%d", pixel.bg.b));
		strcat(res, "m");
	}
	if (pixel.has_fg) {
		strcat(res, "\033[48;2;");
		strcat(res, sprintf("%d", pixel.fg.r));
		strcat(res, ";");
		strcat(res, sprintf("%d", pixel.fg.g));
		strcat(res, ";");
		strcat(res, sprintf("%d", pixel.fg.b));
		strcat(res, "m");
	}
	strcat(res, c);
	strcat(res, "\033[39;49m");
	return (res);
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
