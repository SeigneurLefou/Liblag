#include <ncurses.h>
#include "../includes/lag.h"
#include <unistd.h>

int main(void)
{
	lag_window win;
	lag_buffer	buf;
	lag_window_infos win_infos;
	int width;

	win_infos = (lag_window_infos){
		.flags = IS_RESIZABLE | IS_FULLSCREEN
	};

	if (!lag_init())
		return (1);

	lag_create_window(&win, &win_infos);
	// TODO create a function who create a buffer in the same size of the window
	lag_create_buffer(&buf, win.buf.width, win.buf.height);
	width = 0;

	while (1) {
		lag_autoresize_window(&win);

		lag_clear_window(&win);
		lag_clear_buffer(&buf);
		lag_draw_pixel(&buf, width, 30, '#');
		lag_draw_line(&buf, 4, 3, 30, 20, '*');
		lag_draw_line(&buf, 20, 10, 80, 2, '|');
		lag_draw_rectangle(&buf, 0, 0, 40, 20, '*', DEFAULT);
		lag_draw_rectangle(&buf, 80, 4, 90, 20, '|', FILL);
		lag_blit_buffer(&buf, &win.buf, 0, 0);
		// TODO add a lag_blit_window to pass only the &win
		lag_render_window(&win);

		width = (width + 1) % win.infos->width;
		usleep(50000);
	}
	lag_destroy_buffer(&buf);
	lag_destroy_window(&win);
	return (0);
}
