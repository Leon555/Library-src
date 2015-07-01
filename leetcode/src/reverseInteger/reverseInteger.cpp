#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class solution
{
public:
	// two approaches:
	// 1*, itoa --> reverse char --> atoi
	// 2, rearrange numbers
	int reverse(int x)
	{
		// INT_MIN -2,147,483,647
		char sint[12];
		sprintf(sint, "%d", x);

		size_t start = 0;
		if(sint[0] == '-')
			start = 1;

		// remove the trailing zeros
		size_t len = strlen(sint);
		while(sint[len-1] == '0')
			sint[--len] = '\0';
			
		// reverse string, pay additional attention to end
		// odd/even is irrelevant
		for(int i = start; i < (start+len)/2; i++){
			size_t end = len-1;
			end -= start ? (i-1) : i;
			char temp = sint[i];
			sint[i] = sint[end];
			sint[end] = temp;
		}

		//ignore overflow
		return atoi(sint);
	}
};

int main(int argc, char* argv[])
{
	solution sol;

	// test numbers: 0, -0, (-)1, (-)12, (-)123, (-)1234, 100000000003 
	int ret = sol.reverse(atoi(argv[1]));

	printf(" input is |%s|\noutput is |%d|\n", argv[1], ret);
}
