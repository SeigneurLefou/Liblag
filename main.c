#include <ncurses.h>
#include "includes/lag.h"
#include <unistd.h>

int main(void)
{
    lag_window win;
    lag_window_infos win_infos;
    int width;

    win_infos = (lag_window_infos){
        .width = 20,
        .height = 10,
        .row = 2,
        .col = 2,
        .flags = IS_RESIZABLE
    };

    if (!lag_init())
        return (1);

    lag_init_window(&win, &win_infos);
    width = 0;

    while (1) {
		lag_autoresize_window(&win);

        werase(win.win);
        mvwprintw(win.win, 5, width, "#");
        wrefresh(win.win);

        width = (width + 1) % win.infos->width;
        napms(100);
    }

    lag_destroy_window(&win);
    endwin();
    return (0);
}
