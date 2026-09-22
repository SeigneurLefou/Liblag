#include "lag_event.h"

volatile sig_atomic_t g_lag_running = 1;
volatile sig_atomic_t g_lag_resized = 0;

static lag_signal_callbacks g_sig_callbacks = {0};

static void lag_signal_handler(int sig) {
	if (sig == SIGINT || sig == SIGTERM) {
		g_lag_running = 0;
		if (g_sig_callbacks.on_quit.func) {
			g_sig_callbacks.on_quit.func(g_sig_callbacks.on_quit.args);
		}
	} else if (sig == SIGWINCH) {
		g_lag_resized = 1;
		if (g_sig_callbacks.on_resize.func) {
			g_sig_callbacks.on_resize.func(g_sig_callbacks.on_resize.args);
		}
	}
}

bool lag_init_signals(const lag_signal_callbacks *callbacks) {
	if (callbacks) {
		g_sig_callbacks = *callbacks;
	}

	struct sigaction sa = {0};
	sa.sa_handler = lag_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGINT, &sa, NULL) == -1) return false;
	if (sigaction(SIGTERM, &sa, NULL) == -1) return false;
	if (sigaction(SIGWINCH, &sa, NULL) == -1) return false;

	return true;
}

bool lag_poll_event(lag_event *event) {
	if (!event) return false;

	if (!g_lag_running) {
		event->type = LAG_WINDOW_EVENT;
		event->window.type = LAG_WIN_QUIT;
		return true;
	}
	if (g_lag_resized) {
		g_lag_resized = 0;
		event->type = LAG_WINDOW_EVENT;
		event->window.type = LAG_WIN_RESIZE;
		return true;
	}

	event->type = LAG_NONE_EVENT;
	return false;
}
