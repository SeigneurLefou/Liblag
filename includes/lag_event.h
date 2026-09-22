#ifndef LAG_EVENT_H
# define LAG_EVENT_H

# include <stdbool.h>
# include <signal.h>
# include <stddef.h>

typedef enum e_event_type {
	LAG_KEYDOWN,
	LAG_KEYUP,
	LAG_MOUSEDOWN,
	LAG_MOUSEUP,
	LAG_MOUSEWHEEL,
	LAG_WINDOW_EVENT,
	LAG_NONE_EVENT
} lag_event_type;

typedef enum e_event_window {
	LAG_WIN_QUIT,
	LAG_WIN_RESIZE
} lag_event_window;

typedef struct s_lag_callback {
	void (*func)(void *);
	void *args;
} lag_callback;

typedef struct s_lag_signal_callbacks {
	lag_callback on_resize;
	lag_callback on_quit;
} lag_signal_callbacks;

typedef struct s_lag_keyboard_event {
	int scancode;
} lag_keyboard_event;

typedef struct s_lag_mouse_event {
	int scancode;
} lag_mouse_event;

typedef struct s_lag_window_event {
	lag_event_window type;
} lag_window_event;

typedef struct s_lag_event {
	lag_event_type type;
	union {
		lag_window_event   window;
		lag_keyboard_event key;
		lag_mouse_event    mouse;
	};
} lag_event;

extern volatile sig_atomic_t g_lag_running;
extern volatile sig_atomic_t g_lag_resized;

bool lag_init_signals(const lag_signal_callbacks *callbacks);
bool lag_poll_event(lag_event *event);

#endif
