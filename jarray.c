#include "jarray.h"

#define _JAP(ja) (struct _j_array*((char*(&ja))-sizeof(struct _j_array)))
