#ifndef LAG_PATH_H
# define LAG_PATH_H

# include "lag_vec2.h"
# include <stdlib.h>

typedef struct	s_lag_path {
	lag_vec2	point;
	void		*prev;
	void		*next;
}				lag_path;

lag_path	*lag_new_path(lag_vec2 *point);
lag_path	*lag_path_begin(lag_path **path);
lag_path	*lag_path_end(lag_path **path);
bool		lag_path_push_front(lag_path **path, lag_path **new_element);
bool		lag_path_push_back(lag_path **path, lag_path **new_element);
bool		lag_path_insert(lag_path **path, lag_path **new_element, size_t pos);
bool		lag_path_get_pos(lag_path **path, lag_vec2 *element, size_t pos);
size_t		lag_path_size(lag_path **path);
bool		lag_path_clear(lag_path **path);
bool		lag_path_remove(lag_path **path, size_t pos);

#endif
