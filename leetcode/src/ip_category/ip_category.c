#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLASS_A 0
#define CLASS_B 1
#define CLASS_C 2
#define CLASS_D 3
#define CLASS_E 4
#define INVALID 5
#define PRIVATE 6
#define CLASS_A_PRIVATE 7
#define CLASS_B_PRIVATE 8
#define CLASS_C_PRIVATE 9

int str_to_ip_mask(char *ip_str, int ip[4], int mask[4])
{
	int ret = 0;
	int ip_pos = -1;
	int mask_pos = -1;
	int is_mask = 0;
	int len = strlen(ip_str);
	int i = 0;
	char *num;

	while( i < len && ip_pos < 4 && mask_pos < 4 ) {
		int found = strtol(&ip_str[i], &num, 0);
	   	if( found < 0 || found > 255 || num == &ip_str[i] )
	   		return INVALID;		   
		if( found || num != &ip_str[i] ) {
			if( is_mask )
			 	mask[++mask_pos] = found;
			else
				ip[++ip_pos] = found;

			if( *num != '.' && *num != '~' && *num != '\n')
				return INVALID;
			i = num - ip_str;
			
			if( ip_str[i] == '~' )
				is_mask = 1;
		}
			i++;
	}

	return ret;
}

int validation(int ip[4], int mask[4])
{
	int i = 0;
	int j = 0;
	int bit = 1;
	int has_one = 0;
	for(i = 3; i >= 0; i--) {
		for(j = 0; j <= 7; j++) {
			bit = (mask[i] >> j) & 1;
			if( bit == 1 )
				has_one = 1;
			if( has_one == 1 && bit == 0 )
				return INVALID;
		}
	}

	if( ip[0] >=1 && ip[0] <= 126 )
		if( ip[0] == 10 )
			return CLASS_A_PRIVATE;
		else
			return CLASS_A;
	else if( ip[0] >= 128 && ip[0] <= 191 )
		if( ip[0] == 172 && (ip[1] >= 16 && ip[1] <= 31) )
			return CLASS_B_PRIVATE;
		else
			return CLASS_B;
	else if( ip[0] >= 192 && ip[0] <= 223 )
		if( ip[0] == 192 && ip[1] == 168 )
			return CLASS_C_PRIVATE;
		else
			return CLASS_C;
	else if( ip[0] >= 224 && ip[0] <= 239 )
		return CLASS_D;
	else if( ip[0] >= 240 && ip[0] <= 255 )
		return CLASS_E;
	else
		return INVALID;
}

int main()
{
	char ip_str[32];
	int ip[4];
	int mask[4];
	// A/B/C/D/E, invalid, private
	int category[7] = {0, 0, 0, 0, 0, 0, 0};
	
	int ret = 0;
    int i = 0;
	while( fgets(ip_str, sizeof ip_str, stdin) ) {
		//printf("ret=%d %s\n", ret, ip_str);
		ret = str_to_ip_mask(ip_str, ip, mask);
		if(ret == INVALID) {
			category[ret]++;
			continue;
		}
		ret = validation(ip, mask);
		if(ret <= INVALID)
			category[ret]++;
		else {
			category[ret-CLASS_A_PRIVATE]++;
			category[PRIVATE]++;
		}
		for(i = 0; i < 4; i++) {
			ip[i] = -1;
			mask[i] = -1;
		}
		ret = 0;
	}

	for(i = 0; i < 7; i++)
		printf("%d ", category[i]);

	return 0;
}

	
