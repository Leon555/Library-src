#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "utility.h"

void init_array(ADT **array, size_t len, int positive) 
{
    int i, off;
	ADT mod = len * 10;
   	
	if(positive)
		off = -1;
	else
		off = mod/2;

	*array = (int*) malloc (len * sizeof(ADT));
    for(i = 0; i < len; i++) {
        (*array)[i] = rand()%mod - off;
    }
}

