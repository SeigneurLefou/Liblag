#ifndef lag_BUFFER_H
#define lag_BUFFER_H

#include <stdbool.h>
#include <ncurses.h>

typedef struct s_cell {
    char ch;
    short color_pair;
} t_cell;

typedef struct s_buffer {
    int width;
    int height;
    t_cell **cells;
} t_buffer;

t_buffer *lag_create_buffer(int w, int h);
void lag_destroy_buffer(t_buffer *buf);
void lag_clear_buffer(t_buffer *buf);
void lag_clear_screen(void);
void lag_present(WINDOW *win, t_buffer *buf);
bool lag_put_buffer(t_buffer *buf);

#endif
