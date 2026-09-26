#include "lag.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc < 2)
		return 1;
	lag_vec2	point = (lag_vec2){.x = atoi(argv[1]), .y = atoi(argv[2])};
	lag_path	*path = lag_new_path(&point);
	for (int j = 3; j < argc; j += 4) {
		if (!argv[j] || !argv[j + 1]) break;
		point = (lag_vec2){.x = atoi(argv[j]), .y = atoi(argv[j + 1])};
		lag_path *new_path = lag_new_path(&point);
		lag_path_push_front(&path, &new_path);
		if (!argv[j + 2] || !argv[j + 3]) break;
		point = (lag_vec2){.x = atoi(argv[j + 2]), .y = atoi(argv[j + 3])};
		new_path = lag_new_path(&point);
		lag_path_push_back(&path, &new_path);
	}
	point = (lag_vec2){.x = 102, .y = 103};
	lag_path *new_path = lag_new_path(&point);
	if (!lag_path_insert(&path, &new_path, 5)) {
		lag_path_clear(&new_path);
	}
	lag_path_remove(&path, 5);
	lag_vec2 new_point;
	for (int j = 0; lag_path_get_pos(&path, &new_point, j); j++) {
		printf("pos %d -> x : %d, y : %d\n", j, new_point.x, new_point.y);
	}
	lag_path_clear(&path);
	return (0);
}
