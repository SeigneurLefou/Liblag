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
	lag_create_buffer_by_window(&buf, &win);
	width = 0;

	while (1) {
		lag_autoresize_window(&win);

		lag_clear_buffer(&buf);
		werase(win.win); // TODO need to rework this. Maybe a funciton who take a pointer to another to do the loop
		lag_draw_pixel(&buf, width, 0, '#');
		lag_draw_line(&buf, 2, 2, 50, 10, '*');
		lag_draw_line(&buf, 2, 10, 50, 2, '|');
		lag_blit_buffer(&win, &buf, 0, 0);
		wrefresh(win.win);

		width = (width + 1) % win.infos->width;
		napms(50);
	}
	lag_destroy_buffer(&buf);
	lag_destroy_window(&win);
	endwin();
	return (0);
}
