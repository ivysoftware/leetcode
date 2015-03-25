/*
 Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:
  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sys/time.h>
#include <stack>
#include <stdlib.h>
using namespace std;

class Polish{
public:
	int cal(vector<string>& chars)
	{
		int result = 0, a = 0,  b = 0;
		if(chars.size() == 0)
			return result;

		stack<int> values;
		for(unsigned i = 0; i < chars.size(); i ++)
		{
			if( chars[i].size() == 1 &&
				(chars[i][0] == '+' || chars[i][0] == '-' ||chars[i][0] == '*' || chars[i][0] == '/'))
			{
				if(chars.size() == 0)
					return result;
				a = values.top(); values.pop();
				b = values.top(); values.pop();
				if(chars[i][0] == '+')
					values.push(a + b);
				else if(chars[i][0] == '-')
					values.push(a - b);
				else if(chars[i][0] == '*')
					values.push(a * b);
				else if(chars[i][0] == '/')
					values.push(b / a);
				else{
					return result;
				}
			}else{
				a = atoi(chars[i].c_str());
				values.push(a);
			}
		}
		if(values.size() > 1)
			return result;
		else
			result = values.top();
		return result;
	}
};
int main()
{
    //polish
	string array[] = {"4", "13", "5", "/", "+"};
	vector<string> chars;
	chars.assign(array, array + 5);
	Polish testa;
	cout << testa.cal(chars) << endl;
	return 0;
}