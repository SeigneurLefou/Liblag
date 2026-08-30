/**
 * @file lag_ctx.c
 * @brief Context initialization function implementations.
 */

#include "lag_ctx.h"
#include <unistd.h>

bool lag_init(void) {
	printf("\033[2J\033[H");
	return (true);
}
