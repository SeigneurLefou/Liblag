#include "lag_pixel.h"

bool	lag_init_color(lag_color *color, unsigned short r, unsigned short g, unsigned short b) {
	if (r > 1000 || g > 1000 || b > 1000)
		return (false);
	// TODO define the color with init_color
	return (true)
}

bool	lag_init_color(char c, lag_color bg, lag_color fg) {

}
