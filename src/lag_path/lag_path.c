#include "lag_path.h"

lag_path	*lag_new_path(lag_vec2 *point) {
	lag_path	*new_path = malloc(sizeof(lag_path));

	if (!new_path)
		return (NULL);
	new_path->prev = NULL;
	new_path->next = NULL;
	new_path->point.x = point->x;
	new_path->point.y = point->y;
	return (new_path);
}

lag_path	*lag_path_begin(lag_path **path) {
	lag_path	*begin_path = *path;

	if (!begin_path)
		return (NULL);
	while (begin_path->prev) {
		begin_path = begin_path->prev;
	}
	return (begin_path);
}

lag_path	*lag_path_end(lag_path **path) {
	lag_path	*end_path = *path;

	if (!end_path)
		return (NULL);
	while (end_path->next) {
		end_path = end_path->next;
	}
	return (end_path);
}

bool	lag_path_push_front(lag_path **path, lag_path **new_element) {
	lag_path	*begin_path;
	
	if (*new_element || !*path)
	{
		*path = *new_element;
		return (true);
	}
	if (!*new_element)
		return (false);
	begin_path = lag_path_begin(path);
	begin_path->prev = *new_element;
	(*new_element)->next = begin_path;
	return (true);
}

bool	lag_path_push_back(lag_path **path, lag_path **new_element) {
	lag_path	*end_path;
	
	if (*new_element || !*path)
	{
		*path = *new_element;
		return (true);
	}
	if (!*new_element)
		return (false);
	end_path = lag_path_end(path);
	end_path->prev = *new_element;
	(*new_element)->next = end_path;
	return (true);
}

bool	lag_path_insert(lag_path **path, lag_path **new_element, size_t pos) {
	lag_path	*begin_path;
	lag_path	*previous_element;
	int			actual_position = 0;
	
	if (!*path)
		return (false);
	begin_path = lag_path_begin(path);
	while (begin_path->next && actual_position < pos) {
		begin_path = begin_path->next;
		actual_position++;
	}
	if (!begin_path)
		return (false);
	previous_element = begin_path->prev;
	(*new_element)->prev = previous_element;
	(*new_element)->next = begin_path;
	begin_path->prev = *new_element;
	previous_element->next = *new_element;
	return (true);
}

bool	lag_path_get_pos(lag_path **path, size_t pos, lag_vec2 *element) {
	lag_path	*begin_path;
	int			actual_position = 0;
	
	if (!*path)
		return (false);
	begin_path = lag_path_begin(path);
	while (begin_path->next && actual_position < pos) {
		begin_path = begin_path->next;
		actual_position++;
	}
	if (!begin_path)
		return (false);
	element->x = begin_path->point.x;
	element->y = begin_path->point.y;
	return (true);
}

size_t	lag_path_size(lag_path **path) {
	lag_path	*begin_path;
	size_t		len = 0;
	
	if (!*path) 
		return (0);
	begin_path = lag_path_begin(path);
	while (begin_path->next) {
		begin_path = begin_path->next;
		len++;
	}
	return (len);
}
