#include <ncurses.h>
#include "../includes/lag.h"
#include <unistd.h>

int	main(void) {
	lag_buffer buf; 
	lag_color			a;
	lag_color			b;

	lag_init_color(&a, 200, 100, 50);
	lag_init_color(&b, 50, 100, 200);
	lag_pixel			px_hash = { .ch = '#', .has_bg = false, .has_fg = false };

	lag_create_buffer(&buf, (lag_vec2){5, 5});
	lag_draw_circle(&buf, (lag_vec2){10, 10}, 5, px_hash, DEFAULT);
	return (0);
}

// int main(void)
// {
	// lag_window			win;
	// lag_buffer			buf;
	// lag_window_infos	win_infos;
	// int					width;
	// lag_color			a;
	// lag_color			b;
	// int					i = 200;
// 
	// lag_init_color(&a, 200, 100, 50);
	// lag_init_color(&b, 50, 100, 200);
// 
	// lag_pixel			px_hash = { .ch = '#', .has_bg = false, .has_fg = false };
	// lag_pixel			px_star = { .ch = 9605, .fg = a, .bg = b, .has_bg = true, .has_fg = true };
	// lag_pixel			px_pipe = { .ch = '|', .fg = b, .bg = a, .has_bg = true, .has_fg = true };
// 
	// 
	// win_infos = (lag_window_infos){
		// .flags = IS_RESIZABLE | IS_FULLSCREEN
	// };
// 
	// if (!lag_init())
		// return (1);
// 
	// lag_create_window(&win, &win_infos);
	// // TODO create a function who create a buffer in the same size of the window
	// lag_create_buffer(&buf, (lag_vec2){win.buf.width, win.buf.height});
	// width = 0;
// 
	// while (i--) {
		// lag_autoresize_window(&win);
// 
		// lag_clear_window(&win);
		// lag_clear_buffer(&buf);
		// 
		// lag_draw_pixel(&buf, (lag_vec2){width, 30}, px_hash);
		// lag_draw_line(&buf, (lag_vec2){4, 3}, (lag_vec2){30, 20}, px_star);
		// lag_draw_line_thickness(&buf, (lag_vec2){20, 10}, (lag_vec2){80, 2}, px_pipe, 1);
		// lag_draw_rectangle(&buf, (lag_vec2){0, 0}, (lag_vec2){40, 20}, px_star, DEFAULT);
		// lag_draw_rectangle(&buf, (lag_vec2){80, 4}, (lag_vec2){90, 20}, px_pipe, FILL);
		// 
		// lag_blit_buffer(&buf, &win.buf, (lag_vec2){0, 0});
		// // TODO add a lag_blit_window to pass only the &win
		// lag_render_window(&win);
// 
		// width = (width + 1) % win.infos->width;
		// usleep(50000);
	// }
	// 
	// lag_destroy_buffer(&buf);
	// lag_destroy_window(&win);
	// return (0);
// }
