#ifndef lag_BUFFER_H
#define lag_BUFFER_H

#include <string.h>
#include <stdbool.h>
#include <ncurses.h>
#include <stdlib.h>
#include "lag_window.h"
#include "lag_utils.h"

typedef struct s_lag_buffer {
    int		width;
    int		height;
    char	*content;
}	lag_buffer;

bool	lag_create_buffer(lag_buffer *buffer, int w, int h);
bool lag_create_buffer_by_window(lag_buffer *buf, lag_window *win);
bool	lag_destroy_buffer(lag_buffer *buf);
bool	lag_clear_buffer(lag_buffer *buf);
bool	lag_blit_buffer(lag_window *win, lag_buffer *buf, uint sx, uint sy);

#endif
