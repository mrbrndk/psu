#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>
using namespace std;

#if defined(max)
#undef max
#endif

struct Stack
{
	char value;
	Stack* next;
};

void push(char value, Stack** next);
char pop(Stack** stk);
int priority(char value);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (1)
	{
		cout << "Введите выражение: ";
		Stack* stk = nullptr;
		string input;
		string output;
		getline(cin, input); // читаем строку из потока ввода
		if (input.empty()) break; // если пусто прерываем
		stringstream ss(input); // записываем строку в другой поток
		char token = 0;
		while (!ss.eof()) // извлекаем по одному значению до конца потока
		{
			ss >> token;
			if (ss.fail())
			{
				ss.clear();
				ss.ignore(1, '\n');
				continue;
			}
			if ((token >= '0' && token <= '9') || // если переменная или константа добавляем в строку вывода
				(token >= 'a' && token <= 'z')) output.push_back(token);
			else if (token == '(') push(token, &stk); // если открывающаяся скобка добавляем в стек 
			else if (token == ')') // если закрывающаяся скобка
			{
				token = pop(&stk);
				while (token != '(')
				{ // извлекаем все значения до открывающейся скобки
					output.push_back(token); // добавляем в строку вывода
					token = pop(&stk);
				}
			}
			else
			{ // если знак операции
				if (stk != nullptr)
				{
					while (priority(stk->value) >= priority(token))
					{ // пока приоритет верхнего элемента в стеке больше приоритета текущего 
						output.push_back(pop(&stk)); // добавляем в вывод извлеченый элемент
						if (stk == nullptr) break;
					}
				}
				push(token, &stk); // добавляем в стек текущий элемент
			}
		}
		while (stk != nullptr) // когда строка прочитана и если в стеке что-то есть
		{
			token = pop(&stk); // извлекаем и добавляем в вывод
			if (token != 0) output.push_back(token);
		}
		cout << "ПОЛИЗ: " << output << endl; // вывод
	}
	system("pause");
	return 0;
}

void push(char value, Stack** next)
{ // добавить в стек элемент
	Stack* item = new Stack;
	item->value = value;
	item->next = *next;
	*next = item;
}

char pop(Stack** stk)
{ // удалить элемент из стека
	if (*stk == nullptr) return 0;
	char token = (*stk)->value;
	Stack* tmp = *stk;
	*stk = (*stk)->next; // записали следующий элемент стека
	delete tmp; // удалили элемент стека
	return token;
}

int priority(char value)
{ // возвращает приоритет операции
	switch (value)
	{
		case '*': return 2;
		case '/': return 2;
		case '+': return 1;
		case '-': return 1;
		default: return 0;
	}
}