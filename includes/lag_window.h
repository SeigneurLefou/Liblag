#ifndef LAG_WINDOW_H
# define LAG_WINDOW_H

# include <sys/ioctl.h>
# include <strings.h>
# include <unistd.h>
# include "lag_buffer.h"

typedef enum e_lag_window_flags {
	IS_FULLSCREEN = 1,
	IS_RESIZABLE  = 2
} lag_window_flags;

typedef struct s_lag_window_infos {
	unsigned int		width;
	unsigned int		height;
	unsigned int		row;
	unsigned int		col;
	lag_window_flags	flags;
} lag_window_infos;

typedef struct s_lag_window {
	lag_buffer			buf;
	lag_window_infos	*infos;
	float				w_ratio;
	float				h_ratio;
}	lag_window;

bool	lag_create_window(lag_window *win, lag_window_infos *win_infos);
bool	lag_clear_window(lag_window *win);
bool	lag_destroy_window(lag_window *win);
bool	lag_render_window(lag_window *win);
bool	lag_autoresize_window(lag_window *win);
bool	lag_resize_window(lag_window *win, unsigned int width, unsigned int height);

#endif /* LAG_WINDOW_H */
