#include "containers.h"
#undef DATA_TYPE
#define DATA_TYPE double
#define COMPARE_EXPRESSION(A, B) (B > A ? -1 : B != A)
#include "dlistgen.c"
#undef DATA_TYPE
