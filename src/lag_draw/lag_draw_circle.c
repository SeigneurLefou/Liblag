#include "lag_draw.h"

bool lag_draw_circle(lag_buffer *buf, lag_vec2 pos, uint radius, lag_pixel pixel, lag_draw_enum flags) {
	uint		diameter = 2 * radius + 1;
	bool		*pre_buffer = calloc(diameter * diameter, sizeof(bool));
	int			x = radius, y = 0, p = 1 - radius;
	char		quadrants[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
	bool		is_in_shape;
	// lag_vec2	start_pos;

	while (x >= y) {
		for (uint i = 0; i < 4; i++) {
			int	j = quadrants[i][0], k = quadrants[i][1];
			pre_buffer[(j * x + radius) * diameter + (k * y + radius)] = true;
			pre_buffer[(k * y + radius) * diameter + (j * x + radius)] = true;
		}
		x = x - ((p > 0) ? 1 : 0);
		y++;
		p += (p > 0) ? (1 - 2 * x + 2 * y) : 1 + 2 * y; 
	}
	if (flags & FILL) {
		for (uint posy = 0; posy < radius; posy++) {
			is_in_shape = false;
			for (uint posx = 0; posx < radius; posx++) {
				if (pre_buffer[posy * radius + posx]) {
					is_in_shape = !is_in_shape;
				}
				if (!pre_buffer[posy * radius + posx] && is_in_shape) {
					pre_buffer[posy * radius + posx] = true;
				}
			}
		}
	}
	for (uint posy = 0; posy < radius; posy++) {
		for (uint posx = 0; posx < radius; posx++) {
			printf("%b, ", pre_buffer[posy * radius + posx]);
		}
		printf("\n");
	}
	free(pre_buffer);
	return (true);
}
