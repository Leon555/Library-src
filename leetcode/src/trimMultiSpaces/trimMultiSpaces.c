#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRI(i)  str ## i 

void trimMultiSpaces(char *pstr)
{
	char *p = pstr; // pointer to advance step by step
	char *s = pstr; // pointer to record the first space character
	int flag = 0;   // flag to record the current word/space status, 0: space, 1: word
	size_t snum = 0; // number of spaces
	size_t len = strlen(pstr);
	char *end = pstr+len;

	while(p && *p && *p==' ') {
		p++;
		snum++;
	}
	
	if( p > s )
		memmove(s, p, end+1-p);

	p = s;
	snum = 0;
	while(p && *p) {
		if( *p == ' ') {
			if(flag == 1) {
				s = p; // advance to point to space
			}
			flag = 0;
		}
		else{
		   	if(flag == 0 && p-s>1 ){
				memmove(s+1, p, end+1-p);
				p = s; // update p
			}
			flag = 1;
		}
		p++;
	}

	if(*s == ' ' && flag == 0)
		*s = '\0';
}

int main(int argc, char *argv[])
{
	int row = 5;
	char *strsrc[] = {"", "a", "  hi", "  hi   word", "  hi   word    "};
	
	char **str = (char **) malloc ( row * sizeof(char*) );
	for(int i = 0; i < row; i++){
		int sizei = strlen(strsrc[i]);
		str[i] = (char *) malloc( sizei * sizeof(char) );
		memmove(str[i], strsrc[i], sizei);
		
		printf("|%s|\n", strsrc[i]);
		trimMultiSpaces(str[i]);
		printf("|%s|\n", str[i]);
	}
}
