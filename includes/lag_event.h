#ifndef LAG_EVENT_H
# define LAG_EVENT_H

# include <stdbool.h>
# include <signal.h>
# include <stddef.h>

typedef enum e_event_type {
	EVENT_NONE = 0,
	EVENT_KEY_PRESS,
	EVENT_RESIZE,
	EVENT_QUIT
} lag_event_type;

typedef struct s_lag_event {
	lag_event_type	type;
	int key;
	// TODO use a union for event for use less memory
} lag_event;

extern volatile sig_atomic_t	g_lag_running;
extern volatile sig_atomic_t	g_lag_resized;

bool	lag_init_signals(void);
bool	lag_poll_event(lag_event *event);

#endif
