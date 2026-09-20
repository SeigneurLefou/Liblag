#include "lag_event.h"
#include <signal.h>
#include <stddef.h>

volatile sig_atomic_t g_lag_running = 1;
volatile sig_atomic_t g_lag_resized = 0;

static void lag_signal_handler(int sig) {
	if (sig == SIGINT || sig == SIGTERM) {
		g_lag_running = 0;
	} else if (sig == SIGWINCH) {
		g_lag_resized = 1;
	}
}

bool lag_init_signals(void) {
	struct sigaction sa = {0};

	sa.sa_handler = lag_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGINT, &sa, NULL) == -1) return false;
	if (sigaction(SIGTERM, &sa, NULL) == -1) return false;
	if (sigaction(SIGWINCH, &sa, NULL) == -1) return false;

	return true;
}

bool lag_poll_event(t_lag_event *event) {
	if (!event) return false;

	if (!g_lag_running) {
		event->type = lag_EVENT_QUIT;
		return true;
	}
	if (g_lag_resized) {
		g_lag_resized = 0;
		event->type = lag_EVENT_RESIZE;
		return true;
	}

	event->type = lag_EVENT_NONE;
	return false;
}
