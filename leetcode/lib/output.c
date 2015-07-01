#include "lib_leon.h"

void print_array(int *array, size_t len) {
    int i;
    for(i = 0; i < len; i++) {
        printf("%d, ", array[i]);
    }
    printf("%d\n", array[i]);
}
