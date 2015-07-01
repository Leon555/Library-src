#include <stdio.h>

int main(int argc, char *argv[])
{
	int a[5] = {1, 2, 3, 4, 5};

	int *b = (int *)(&a+1);

	printf("%d, %d\n", *(a+1), *(b-1));

	int c[4][4];
	int **d;
	int (*e)[4];

	func(2014);

	fun(c);
	fun(d);
	fun(e);
}

void fun(int *p[4]){
}

int func(unsigned int n) {
	int m = 0;

	while(n+1){
		m++;
		n = n | (n+1);
	}
	printf("m: %d\n", m);
	return m;
}
