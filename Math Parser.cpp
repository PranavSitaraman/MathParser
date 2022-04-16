#include <iostream>
#include <list>
using namespace std;
struct value
{
	char ch;
	float num;
	bool type;
};
void mathparserrun()
{
	list<value> in, top;
	char ord[255] = { 0 }; ord['^'] = 3; ord['/'] = 2; ord['*'] = 2; ord['%'] = 2; ord['+'] = 1; ord['-'] = 1;
	char a;
	cout << "Enter a mathematical expression in infix form: ";
	while ((a = getchar()) != '\n')
	{
		if (a == ' ') continue;
		else if ((a >= '0' && a <= '9') || a == '.')
		{
			float dec;
			ungetc(a, stdin); scanf("%f", &dec);
			in.push_back({ NULL, dec, false });
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
		else if (a != '(' && top.empty() == false && ord[top.front().ch] >= ord[a])
		{
			in.push_back(top.front());
			top.pop_front();
			top.push_front({ a, NULL, true });
		}
		else top.push_front({ a, NULL, true });
	}
	while (top.empty() == false)
	{
		in.push_back(top.back());
		top.pop_back();
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
			top.push_front({ NULL, result, false });
		}
		in.pop_front();
	}
	float answer = top.front().num;
	top.pop_front();
	cout << "Final value: " << answer;
}