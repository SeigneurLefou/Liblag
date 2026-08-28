/**
 * @file lag_ctx.h
 * @brief Context initialization utilities for the LAG library.
 */

#ifndef LAG_CTX_H
#define LAG_CTX_H

#include <stdbool.h>
#include <ncurses.h>

/**
 * @brief Initializes the ncurses screen context and default input/color modes.
 *
 * Disables line buffering (cbreak), hides typed characters (noecho),
 * hides the cursor, enables special keyboard keys on stdscr, and initializes
 * colors if supported by the terminal.
 *
 * @return true if ncurses initialized successfully, false otherwise.
 */
bool lag_init(void);

#endif /* LAG_CTX_H */
