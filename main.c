#include <ncurses.h>
#include "includes/lag.h"
#include <unistd.h>

int main()
{
	lag_window			win;
	lag_window_infos	win_infos;

	win_infos = (lag_window_infos){.width = 20, .height = 10, .row = 2, .col = 2, .flags = IS_RESIZABLE};
	lag_init();
	lag_init_window(&win, &win_infos);
	while (0) {refresh();}
	lag_destroy_window(&win);
}
