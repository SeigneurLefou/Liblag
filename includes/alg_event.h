#ifndef ALG_EVENT_H
#define ALG_EVENT_H

#include <stdbool.h>

typedef enum e_event_type {
    ALG_EVENT_NONE = 0,
    ALG_EVENT_KEY_PRESS,
    ALG_EVENT_RESIZE,
    ALG_EVENT_QUIT
} t_event_type;

typedef struct s_alg_event {
    t_event_type type;
    int key;
} t_alg_event;

bool alg_poll_event(t_alg_event *event);

#endif
