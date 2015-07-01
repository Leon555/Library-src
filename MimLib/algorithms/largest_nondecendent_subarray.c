#include <stdio.h>
#include <stdio.h>

int array[10] = {1, 3, 2, 4, 8, 7, 9, 10, 2, 5};
int aux[10]   = {1};

int lns(int *arr, size_t len)
{
    arr = array;
    len = 10;
    
    aux[0] = 1;
    int max = 1;
    for(int i = 1; i < len; i++) {
        aux[i] = 1;
        for(int j = 0; j < i; j++) {
            if(arr[i] >= arr[j]) {
                aux[i]++;
            }
        }
    }
    for(int i = 0; i < len; i++) {
        printf("%d ", aux[i]);
    }
}

int main()
{
    int ret = lns(array, 10);
}