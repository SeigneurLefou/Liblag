#ifndef LAG_TIME_H
# define LAG_TIME_H

# include <stdint.h>

uint32_t lag_get_ticks(void);
void lag_delay(uint32_t ms);

#endif
