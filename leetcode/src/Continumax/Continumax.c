#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "CUnit/Basic.h"

#define IS_NUMBER(ch) ( (ch) >= '0' && (ch) <= '9' )

static unsigned int Continumax( char **pOutputstr, char *intputstr )
{
	unsigned int maxlen = 0;
	unsigned int curlen = 0;
	char *start = intputstr;
    char *out = *pOutputstr;
    unsigned int i = 0;

	while( start != NULL && *start != '\0' ) {
		if( IS_NUMBER(*start) ) {
			while( *start != '\0' && IS_NUMBER(*start) ) {
				curlen++;
				start++;
			}
		}
		else {
			while( *start != '\0' && !IS_NUMBER(*start) ) {
				start++;
			}
		}

		if( curlen >= maxlen ) {
            *pOutputstr = start - curlen;
		    maxlen = curlen;
        }
		curlen = 0;
	}
    
    out = (char *) malloc (maxlen + 1);
    if(out == NULL)
        return 0;
    start = *pOutputstr;
    *pOutputstr = out;
    for(i = 0; i < maxlen; i++)
        *out++ = *(start + i);
    *(*pOutputstr + maxlen) = '\0';
    
	return maxlen;
}

int main()
{
	unsigned int len = 0; 
    int i = 0;
	char *outstr = NULL;
	char *str[6];
    
    str[0] = NULL;
    str[1] = "";
    str[2] = "a";
    str[3] = "aa123afds12a3";
    str[4] = "123";
    str[5] = "aa123afds124";
    
    for(i = 0; i < 6; i++) {
        outstr = NULL;
        len = Continumax( &outstr, str[i]);
        printf("length: %u \nString: %s\n", len, outstr);
        free(outstr);
    }
    outstr = NULL;
    
    return 0;
}



