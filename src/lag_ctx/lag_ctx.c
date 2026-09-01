/**
 * @file lag_ctx.c
 * @brief Context initialization function implementations.
 */

#include "lag_ctx.h"
#include <unistd.h>

bool lag_init(void) {
	printf(
			"\033[2J"		// Erase Screen
			"\033[H"		// Go to home (0,0)	
			"\033[?25l"		// Cursor masking
			);
	return (true);
}
