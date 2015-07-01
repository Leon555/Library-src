#include "lib_leon.h"

void init_array(int **array, size_t len, int positive) 
{
    int i, off;
	int mod = len * 10;
   	
	if(positive)
		off = -1;
	else
		off = mod/2;

	*array = (int*) malloc (len * sizeof(int));
    for(i = 0; i < len; i++) {
        (*array)[i] = rand()%mod - off;
    }
}

