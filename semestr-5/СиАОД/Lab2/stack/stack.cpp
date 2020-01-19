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
Stack* pop(Stack* stk);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Вводите последовательности скобок:" << endl;
	while (1)
	{
		string str;
		getline(cin, str);//читаем строку из потока ввода
		if (str.empty()) break;//если строка пуста завершаем программу
		stringstream ss(str);//записываем строку в другой поток
		Stack* stk = nullptr;
		char value = 0;
		while (!ss.eof())//извлекаем по одному значению до конца потока
		{
			ss >> value;
			if (ss.fail())
			{
				ss.clear();
				ss.ignore(1, '\n');
				continue;
			}
			if (stk == nullptr)
			{
				push(value, &stk);//создаем элемент
				continue;
			}

			//если текущая скобка соответствует верхней в стеке
			if ((stk->value == '(' && value == ')') || 
				(stk->value == '[' && value == ']') || 
				(stk->value == '{' && value == '}'))
				stk = pop(stk);//удаляем элемент
			else
				push(value, &stk);//создаем элемент

		}
		if (stk == nullptr) cout << "YES" << endl << endl;//если стек пуст
		else
		{//если что-то осталось
			cout << "NO" << endl << endl;
			while(stk != nullptr) stk = pop(stk);
		}
	}
	system("pause");
	return 0;
}

void push(char value, Stack** next)
{//добавить в стек
	Stack* item = new Stack;
	item->value = value;
	item->next = *next;
	*next = item;
}

Stack* pop(Stack* stk)
{//удалить из стека
	if (stk == nullptr) return nullptr;
	Stack* next = stk->next;//записали следующий элемент стека
	delete stk;//удалили элемент стека
	return next;
}