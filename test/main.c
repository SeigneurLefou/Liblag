#include "../includes/lag.h"
#include <unistd.h>
#include <stdio.h>
#include <time.h>

typedef struct s_game {
	lag_window *win;
	lag_buffer *buf;
	bool        is_running;
} t_game;

static void on_window_quit(void *arg) {
	t_game *game = (t_game *)arg;
	game->is_running = false;
}

static void on_window_resize(void *arg) {
	t_game *game = (t_game *)arg;

	lag_autoresize_window(game->win);
	lag_destroy_buffer(game->buf);
	lag_create_window_buffer(game->buf, game->win);
}

int main(void)
{
	t_game            game = {0};
	lag_window        win;
	lag_buffer        buf;
	lag_window_infos  win_infos;
	lag_color         a, b;
	lag_pixel         px_hash, px_star, px_pipe;
	lag_event         event;

	struct timespec   last_time, current_time;
	int               frames = 0;
	int               width = 0;
	char              fps_str[32] = "FPS: 0";

	if (!lag_init()) return 1;

	lag_set_color(&a, 200, 100, 50);
	lag_set_color(&b, 50, 100, 200);

	lag_set_pixel(&px_hash, "#", NULL, NULL);
	lag_set_pixel(&px_star, "▅", &a, &b);
	lag_set_pixel(&px_pipe, "|", &b, &a);

	win_infos = (lag_window_infos){
		.flags = IS_RESIZABLE | IS_FULLSCREEN
	};

	if (!lag_create_window(&win, &win_infos)) return 1;
	if (!lag_create_window_buffer(&buf, &win)) {
		lag_destroy_window(&win);
		return 1;
	}

	game.win = &win;
	game.buf = &buf;
	game.is_running = true;

	lag_signal_callbacks sig_cbs = {
		.on_quit   = { .func = on_window_quit,   .args = &game },
		.on_resize = { .func = on_window_resize, .args = &game }
	};

	if (!lag_init_signals(&sig_cbs)) {
		lag_destroy_buffer(&buf);
		lag_destroy_window(&win);
		return 1;
	}

	clock_gettime(CLOCK_MONOTONIC, &last_time);

	while (game.is_running) {
		while (lag_poll_event(&event)) {
			if (event.type == LAG_WINDOW_EVENT) {
				if (event.window.type == LAG_WIN_QUIT && sig_cbs.on_quit.func)
					sig_cbs.on_quit.func(sig_cbs.on_quit.args);
				else if (event.window.type == LAG_WIN_RESIZE && sig_cbs.on_resize.func)
					sig_cbs.on_resize.func(sig_cbs.on_resize.args);
			}
		}

		frames++;
		clock_gettime(CLOCK_MONOTONIC, &current_time);
		double elapsed = (current_time.tv_sec - last_time.tv_sec) +
		                 (current_time.tv_nsec - last_time.tv_nsec) / 1e9;
		if (elapsed >= 1.0) {
			snprintf(fps_str, sizeof(fps_str), "FPS: %d", (int)(frames / elapsed));
			frames = 0;
			last_time = current_time;
		}

		lag_clear_window(&win);
		lag_clear_buffer(&buf);

		lag_draw_pixel(&buf, (lag_vec2){width, 30}, &px_hash);
		lag_draw_line(&buf, (lag_vec2){4, 3}, (lag_vec2){30, 20}, &px_star);
		lag_draw_rectangle(&buf, (lag_vec2){1, 0}, (lag_vec2){40, 20}, &px_star, DEFAULT);
		lag_draw_rectangle(&buf, (lag_vec2){80, 4}, (lag_vec2){90, 20}, &px_pipe, FILL);
		lag_draw_circle(&buf, (lag_vec2){10, 10}, 5, &px_hash, DEFAULT);
		lag_draw_circle(&buf, (lag_vec2){20, 20}, 5, &px_hash, FILL);

		lag_draw_text(&buf, (lag_vec2){0, 0}, fps_str, &a, &b);

		lag_blit_window(&win, &buf, (lag_vec2){0, 0});
		lag_render_window(&win);

		width = (width + 1) % win.infos->width;
	}

	lag_destroy_buffer(&buf);
	lag_destroy_window(&win);
	return 0;
}
