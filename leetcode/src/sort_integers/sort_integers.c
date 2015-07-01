#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_ints(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int main()
{
	int ints[50];
	char str[101];
	int num = 0;
	int i = 0;
	int base = 0;  /* the base position for further detection */
	int curr = 0;  /* the current position to be compared */
	int next = 0;  /* next position to be iterated */
	char *start = NULL;
	char *ch = NULL;
	int ret = 0;
	
	memset(str, '\0', 101);

	while( (ret = fscanf(stdin, "%s", str)) != EOF )
    {
        if(ret == 0)
            continue;
        
        start = str;
        ch = str;
        num = 0;
		while( *start ) 
		{
			while( *ch && *ch != ',')
				ch++;
			*ch = '\0';
			ints[num++] = atoi(start);
			start = ++ch;
		}
	
		qsort(ints, num, sizeof(int), compare_ints);
	
        base = 0;
        curr = 0;
        next = 0;
		while( base < num )
		{
			curr = base;
			next = base+1;
			while(next < num)
			{
				if( (ints[next] == ints[curr]) || (ints[next] == ints[curr]+1) )
				{
					curr++;
					next++;
				}
				else
					break;
			}
			printf("%d ", ints[base]);
			if( curr > base )
			{
				printf("%d ", ints[curr]);
				base = curr+1;
			}
			else
				base++;
		}
	
		printf("\n");
		#ifdef DEBUG_TEST
		for(i = 0; i < num; i++)
			printf("%d ", ints[i]);
		printf("\n");
		#endif
		
		memset(str, '\0', 101);
	}
	
	return 0;					
}
