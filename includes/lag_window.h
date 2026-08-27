#ifndef lag_WINDOW_H
# define lag_WINDOW_H

# include <ncurses.h>
# include <sys/ioctl.h>
# include <strings.h>

typedef enum e_lag_window_flags {
	IS_FULLSCREEN = 1,
	IS_RESIZABLE = 2
}	lag_window_flags;

typedef struct s_lag_window_infos {
	unsigned int		width;
	unsigned int		height;
	unsigned int		row;
	unsigned int		col;
	lag_window_flags	flags;
}	lag_window_infos;

typedef struct s_lag_window {
	WINDOW				*win;
	lag_window_infos	*infos;
	float				w_ratio;
	float				h_ratio;
}	lag_window;

void	lag_init_window(lag_window *win,
		lag_window_infos *win_infos);
void	lag_destroy_window(lag_window *win);

#endif
