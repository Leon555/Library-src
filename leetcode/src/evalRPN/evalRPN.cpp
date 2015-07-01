/**
 * The program evaluates the reverse polish notation
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>

using std::cout;
using std::string;
using std::vector;
using std::stack;

class solution
{
public:
	int evalRPN(vector<string> &tokens)
	{
		size_t tsize = tokens.size();
		if(!tsize)
			return 0;

		stack<int> tstk;

		size_t i = 0;

		while(i < tsize || !tstk.empty()) {
			string str;
            int op = 0;
			if(i < tsize) {
				str = tokens[i++];
                char ch1 = (str.c_str())[0];
                char ch2 = (str.c_str())[1];
				// if ch1 is not a number, then op is a operator only when ch2 is NULL
				if(ch1 > '9' || ch1 < '0')
					op = ch2 ? 0 : ch1;
				if(!op)
					tstk.push(atoi(str.c_str()));
            }
            
            if(op){
    			int op1, op2;
    			op2 = tstk.top();
    			tstk.pop();
    			op1 = tstk.top();
    			tstk.pop();

    			int res = 0;
    			switch(op) { 
					// can be written as macro
					// OP(op1, op2, op) ( (op1) #op (op2) )
    				case '+': res = op1 + op2; break;
    				case '-': res = op1 - op2; break;
    				case '*': res = op1 * op2; break;
    				case '/': res = op1 / op2; break;
    				default: break;
    			}
    			tstk.push(res);	
            }
			else if(i == tsize) // exit when no op and no input
				break;
		}
		return tstk.top();		
	}
};


int main(int argc, char* argv[])
{
	vector<string> vec;

	solution sol;
	int ret;
    
	// case 1: empty string
	// case 2: 12 5 +
	// case 2: 2 1 + 3 *
	// case 3: -1 1 * -1 +
	for(int i = 1; i < argc; i++)
		vec.push_back(argv[i]);
    ret = sol.evalRPN(vec);
	cout << ret << '\n';
}
