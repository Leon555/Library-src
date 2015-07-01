#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

using std::string;

class Solution
{
public:
	void reverseWords(string &s)
	{
		const char *str = s.c_str();
		
		char *cstr = (char*) malloc (sizeof(char) * (strlen(str)+1));
		strcpy(cstr, str);
        
        s.clear();

		char *tok = NULL;
		char *pos[1024];
		int num = 0;
		
		tok = strtok(cstr, " ");
		while(tok) {
			pos[num++] = tok;
			tok = strtok(NULL, " ");
		}

		int p = 0;
		while(num > 0) {
			char *st = pos[--num];
			int len = strlen(st);
			s.replace(p, len, st);
			if(num > 0)
				s.replace(p+len, 1, " ");
			p += len+1;
		}
        
		free(cstr);
	}
};

int main(int argc, char *argv[])
{
	string s("the sky is blue");
	string s1("");
	string s2(" ");
	string s3(" 333    88   ");
	solution sol;

	sol.reverseWords(s);
	sol.reverseWords(s1);
	sol.reverseWords(s2);
	sol.reverseWords(s3);

	std::cout << "|" << s << "|" << '\n';
	std::cout << "|" << s1 << "|" << '\n';
	std::cout << "|" << s2 << "|" << '\n';
	std::cout << "|" << s3 << "|" << '\n';
	return 0;
}
