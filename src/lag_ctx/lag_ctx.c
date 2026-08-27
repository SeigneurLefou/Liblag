#include "lag_ctx.h"

bool	lag_init() {
	if (!initscr()) {
		return (false);
	}
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	if (has_colors()) {
		start_color();
	}
	return (true);
}
