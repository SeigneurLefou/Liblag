#include "lag_path.h"

lag_path	*lag_new_path(lag_vec2 *point) {
	lag_path	*new_path;
	
	if (!point)
		return (NULL);
	new_path = malloc(sizeof(lag_path));
	if (!new_path)
		return (NULL);
	new_path->prev = NULL;
	new_path->next = NULL;
	new_path->point.x = point->x;
	new_path->point.y = point->y;
	return (new_path);
}

lag_path	*lag_path_begin(lag_path **path) {
	lag_path	*begin_path;
   
	if (!path)
		return (NULL);
	begin_path = *path;
	if (!begin_path)
		return (NULL);
	while (begin_path->prev) {
		begin_path = begin_path->prev;
	}
	return (begin_path);
}

lag_path	*lag_path_end(lag_path **path) {
	lag_path	*end_path;
   
	if (!path)
		return (NULL);
	end_path = *path;
	if (!end_path)
		return (NULL);
	while (end_path->next) {
		end_path = end_path->next;
	}
	return (end_path);
}

bool	lag_path_push_front(lag_path **path, lag_path **new_element) {
	lag_path	*begin_path;
	
	if (!new_element || !*new_element || !path)
		return (false);
	if (*new_element && !*path)
	{
		*path = *new_element;
		return (true);
	}
	begin_path = lag_path_begin(path);
	begin_path->prev = *new_element;
	(*new_element)->next = begin_path;
	*path = *new_element;
	return (true);
}

bool	lag_path_push_back(lag_path **path, lag_path **new_element) {
	lag_path	*end_path;
	
	if (!new_element || !*new_element || !path)
		return (false);
	if (*new_element && !*path)
	{
		*path = *new_element;
		return (true);
	}
	end_path = lag_path_end(path);
	end_path->next = *new_element;
	(*new_element)->prev = end_path;
	return (true);
}

bool	lag_path_insert(lag_path **path, lag_path **new_element, size_t pos) {
	lag_path	*begin_path;
	lag_path	*previous_element;
	int			actual_position = 0;
	
	if (!path || !*path || !new_element || !*new_element)
		return (false);
	begin_path = lag_path_begin(path);
	while (begin_path->next && actual_position < pos) {
		begin_path = begin_path->next;
		actual_position++;
	}
	if (actual_position != pos && actual_position + 1 != pos)
		return (false);
	if (actual_position + 1 == pos) {
		return (lag_path_push_back(path, new_element));
	}
	previous_element = begin_path->prev;
	if (previous_element) {
		(*new_element)->prev = previous_element;
		previous_element->next = *new_element;
	}
	(*new_element)->next = begin_path;
	begin_path->prev = *new_element;
	return (true);
}

bool	lag_path_get_pos(lag_path **path, lag_vec2 *element, size_t pos) {
	lag_path	*begin_path;
	int			actual_position = 0;
	
	if (!*path)
		return (false);
	begin_path = lag_path_begin(path);
	while (begin_path && begin_path->next && actual_position < pos) {
		begin_path = begin_path->next;
		actual_position++;
	}
	if (!begin_path || actual_position != pos)
		return (false);
	element->x = begin_path->point.x;
	element->y = begin_path->point.y;
	return (true);
}

size_t	lag_path_size(lag_path **path) {
	lag_path	*begin_path;
	size_t		len = 1;
	
	if (!*path) 
		return (0);
	begin_path = lag_path_begin(path);
	while (begin_path->next) {
		begin_path = begin_path->next;
		len++;
	}
	return (len);
}

bool	lag_path_clear(lag_path **path) {
	lag_path	*begin_path;
	lag_path	*last_element;

	if (!path || !*path)
		return (false);
	begin_path = lag_path_begin(path);
	while (begin_path) {
		last_element = begin_path;
		begin_path = begin_path->next;
		free(last_element);
	}
	return (true);
}

bool	lag_path_remove(lag_path **path, size_t pos) {
	lag_path	*begin_path;
	lag_path	*previous_element = NULL;
	lag_path	*next_element = NULL;
	int			actual_position = 0;
	
	if (!path || !*path)
		return (false);
	begin_path = lag_path_begin(path);
	while (begin_path && actual_position < pos) {
		begin_path = begin_path->next;
		actual_position++;
	}
	if (!begin_path)
		return (false);
	previous_element = begin_path->prev;
	next_element = begin_path->next;
	if (previous_element)
	{
		previous_element->next = next_element;
		*path = previous_element;
	}
	if (next_element) {
		next_element->prev = previous_element;
		*path = next_element;
	}
	free(begin_path);
	return (true);
}
