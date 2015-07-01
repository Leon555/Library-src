#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mygetline(char line[], int max)
{
	int nch = 0;
	int c;
	max = max - 1;			/* leave room for '\0' */

	while( (c = getchar()) != EOF )
	{
		if(c == '\n')
			break;

		if(nch < max)
		{
			line[nch] = c;
			nch = nch + 1;
		}
	}

	if(c == EOF && nch == 0)
		return EOF;

	line[nch] = '\0';
	return nch;
}

int main()
{
	char str[100]; 
	int len = 0;
	int pos = 0;
	int flag = 0; /* space flag */
	int cmd_pos = 0; /* current character position of cmds[0] or cmds[1] */
	int i = 0;
	char *cmds[7][2];
	char *response[8];
	int  match[7][2];
	int match_no = 7;
	
	cmds[1][0] = "reset"; 		cmds[1][1] = "";			response[1] = "reset what";
	cmds[2][0] = "reset"; 		cmds[2][1] = "board";		response[2] = "board fault";
	cmds[3][0] = "board"; 		cmds[3][1] = "add";			response[3] = "where to add";
	cmds[4][0] = "board"; 		cmds[4][1] = "delet";		response[4] = "no board at all";
	cmds[5][0] = "reboot";		cmds[5][1] = "backplane";	response[5] = "impossible";
	cmds[6][0] = "backplane"; 	cmds[6][1] = "abort";		response[6] = "install first";
	response[7] = "unkown command";
	
	while( (len = mygetline(str, 100)) != EOF ) 
	{
	#ifdef DEBUG_TEST
		printf("input: %s\n", str);
	#endif
		
		if(len < 1)
			continue;
		if(len > 16) /* longest command: strlen("reboot backplane") */
		{	
			printf("%s\n", response[7]);
			continue;
		}
		
		pos = 0;
		flag = 0;
		cmd_pos = 0;
		memset(match, 0, sizeof(match));
		match[1][1] = 1; /* cmds[1][1] is empty */
		
		do
		{
			if( str[pos] == ' ' )
			{
				flag = 1;
				cmd_pos = 0;
				pos++;
				continue;
			}
			for(i = 1; i <= 6; i++)
			{
				if(str[pos] == cmds[i][flag][cmd_pos])
					match[i][flag] = 1;
				else
					match[i][flag] = 0;
			}
			pos++;	
			cmd_pos++;
		}
		while( str[pos] );
		
		match_no = 7;
		for(i = 1; i <= 6; i++)
		{
			if( match[i][0] == 1 && match[i][1] == 1)
			{
				if(match_no == 7)   /* first match */
					match_no = i;
				else				/* have a match already */
				{
					match_no = 7; 
					break;
				}
			}
		}
		
	#ifdef DEBUG_TEST
		printf("result: %s\n\n", response[match_no]);
	#endif
	
	#ifndef DEBUG_TEST
		printf("%s\n", response[match_no]);
	#endif
			
	}
	
	return 0;					
}
