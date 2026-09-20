#ifndef LAG_EVENT_H
# define LAG_EVENT_H

# include <stdbool.h>
# include <signal.h>

typedef enum e_event_type {
	lag_EVENT_NONE = 0,
	lag_EVENT_KEY_PRESS,
	lag_EVENT_RESIZE,
	lag_EVENT_QUIT
} t_event_type;

typedef struct s_lag_event {
	t_event_type type;
	int key;
} t_lag_event;

extern volatile sig_atomic_t g_lag_running;
extern volatile sig_atomic_t g_lag_resized;

bool	lag_init_signals(void);
bool	lag_poll_event(t_lag_event *event);

#endif
