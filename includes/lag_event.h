#ifndef lag_EVENT_H
#define lag_EVENT_H

#include <stdbool.h>

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

bool lag_poll_event(t_lag_event *event);

#endif
