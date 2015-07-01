#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

using std::string;

class Solution {
public:
    void reverseWords(string &s) {
        string result;
        int pos = 0;
        for (int i = 0; i < s.size(); i ++){
            if (s[i] == ' '){
                if (i > pos )
                    result = s.substr(pos,i-pos)+ " " + result ;
                pos = i + 1;
            }
            else if (i == s.size()-1)
                result = s.substr(pos,s.size()-pos)+" "+result;
        }
        s = result.substr(0,result.size()-1) ;
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
