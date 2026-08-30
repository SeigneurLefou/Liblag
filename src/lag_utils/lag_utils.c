#include "lag_utils.h"

void*	memdup(const void* mem, size_t size) {
	void* out = malloc(size);

	if(out != NULL)
		 memcpy(out, mem, size);

	return out;
}
