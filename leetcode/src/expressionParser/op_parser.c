#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stack>

using std::string;
using std::stack;

int co(char a, char b) {  
    if (a == '+' || a == '-') {  
        if (b == '+' || b == '-' || b == ')' || b == '#')  
            return 1;
        return -1;
    }  
    if (a == '(' || a == '#') {  
        if (a == '(' && b == ')')  
            return 0; // a==b  
        else if (a == '(' && b == '#')  
            return 2;
        else if (a == '#' && b == ')')  
            return 2;  
        else if (a == '#' && b == '#')  
            return 0;  
        else  
            return -1;  
    }  
    if (a == ')') {  
        if (b == '(')  
            return 2;  
        else  
            return 1;  
    }  
    return 0;  
}  

bool isNum(char ch) {  
    if ((ch >= '0' && ch <= '9') || ch == '.')  
        return true;  
    return false;  
}  

bool isSign(char ch) {  
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' ||   
        ch == ')' || ch == '#')  
        return true;  
    return false;  
}  

double operation(int op, double a, double b) {
    switch(op)  {
        case '+': return a + b; 
        case '-': return b - a; 
        case '*': return a * b; 
        case '/': return b / a;
    } 
    return 0;  
}  

double calculate(string &s) {  
    s += "#";  // mark the bottom of stack
    int i = 0; 
    char c; 
    stack<double> num;
    stack<char> op;
    op.push('#');
    c = s.substr(i, i + 1).at(0);
    while (c != '#' || op.top() != '#')
    {  
        if (!isSign(c)) 
        {  
            int start = i;  
            int end = 0;  
            while (!isSign(s.substr(i, i + 1).at(0)))  
                end = i++;
            double m = std::strtod(s.substr(start, end + 1).c_str(), nullptr);
            num.push(m);
            c = s.substr(i, i + 1).at(0);
        } else
        {  
            switch (co(op.top(), c))
            {  
            case -1:
                op.push(c);
                i++;  
                c = s.substr(i, i + 1).at(0);  
                break;  
            case 0:
                op.pop();
                i++;  
                c = s.substr(i, i + 1).at(0);  
                break;  
            case 1:
                double a = num.top();  
                num.pop();  
                double b = num.top();
                num.pop(); 
                char ss = op.top();
                op.pop();
                num.push(operation(ss, a, b));  
                break;  
            }  
        }  
    }  
    return num.top();
}

int main(){
    printf("%s\n", calculate(string("1+2*(3+4)")));  
        //System.out.println(MyCal.calculate("1+2*3+5+Math.max(1,3)"));  
} 