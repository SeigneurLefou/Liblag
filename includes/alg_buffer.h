#ifndef ALG_BUFFER_H
#define ALG_BUFFER_H

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

t_buffer *alg_create_buffer(int w, int h);
void alg_destroy_buffer(t_buffer *buf);
void alg_clear_buffer(t_buffer *buf);
void alg_clear_screen(void);
void alg_present(WINDOW *win, t_buffer *buf);
bool alg_put_buffer(t_buffer *buf);

#endif
