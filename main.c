#include "includes/alg.h"
#include <unistd.h>

int main()
{
	t_alg_window	win;
	alg_init();
	alg_init_window(&win, 10, 10, 0, 0);
	sleep(1);
	write(1, "FISH\n", 5);
	sleep(1);
	alg_destroy_window(&win);
}
