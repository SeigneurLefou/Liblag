#include "lag_ctx.h"

bool lag_init(void) {
	write(STDOUT_FILENO, "\033[2J\033[H\033[?25l", strlen("\033[2J\033[H\033[?25l"));
	return (true);
}
