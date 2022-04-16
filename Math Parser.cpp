#include <iostream>
#include <list>
#include <cmath>
#include <string>
using namespace std;
struct value
{
	char ch;
	float num;
	bool type;
};
int main()
{
	list<value> in, top; string expression;
	char ord[255] = { 0 }; ord['^'] = 3; ord['/'] = 2; ord['*'] = 2; ord['+'] = 1; ord['-'] = 1;
	cout << "Enter a mathematical expression in infix form: ";
	getline(cin, expression);
	for (int i = 0; i < expression.length(); i++)
	{
		char a = expression[i];
		if (a == ' ') continue;
		else if ((a >= '0' && a <= '9') || a == '.')
		{
			string dec = "";
			while (expression[i] == '.' || (expression[i] >= '0' && expression[i] <= '9'))
			{
				dec += expression[i];
				i++;
			}
			i--;
			in.push_back({ '\0', stof(dec), false });
		}
		else if (a == ')')
		{
			value val = top.front();
			top.pop_front();
			while (val.type == true && val.ch != '(')
			{
				in.push_back(val);
				val = top.front();
				top.pop_front();
			}
		}
		else
		{
			top.push_front({ a, 0.0, true });
			while (true)
			{
				a = top.front().ch;
				top.pop_front();
				if (a == '(' || top.empty() == true)
				{
					top.push_front({ a, 0.0, true });
					break;
				}
				if (ord[top.front().ch] >= ord[a])
				{
					in.push_back(top.front());
					top.pop_front();
					top.push_front({ a, 0.0, true });
				}
				else
				{
					top.push_front({ a, 0.0, true });
					break;
				}
			}
		}
	}
	while (top.empty() == false)
	{
		in.push_back(top.front());
		top.pop_front();
	}
	while (in.empty() == false)
	{
		if (in.front().type == false) top.push_front(in.front());
		else
		{
			float val2 = top.front().num;
			top.pop_front();
			float val1 = top.front().num;
			top.pop_front();
			float result = 0;
			switch (in.front().ch)
			{
				case '+': result = val1 + val2; break;
				case '-': result = val1 - val2; break;
				case '*': result = val1 * val2; break;
				case '/': result = val1 / val2; break;
				case '%': result = int(val1) % int(val2); break;
				case '^': result = pow(val1, val2); break;
			}
			top.push_front({ '\0', result, false });
		}
		in.pop_front();
	}
	float answer = top.front().num;
	top.pop_front();
	cout << "Final value: " << answer;
}
