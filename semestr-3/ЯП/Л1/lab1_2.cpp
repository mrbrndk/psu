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
	double value;
	Stack *next;
};

template <typename T>
void get_value(T &value);
Stack *create();
void push(double value, Stack **next);
Stack *pop(Stack *stk);
void output(Stack *stk);
void clear(Stack *stk);
void process();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int n = 0;//кол-во стеков для обработки
	cout << "Введите количество стеков для обработки: ";
	get_value(n);

	cout << "Введите значения элементов стека через пробел:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << ": ";
		process();
	}
	system("pause");
	return 0;
}

template <typename T>
void get_value(T &value)
{
	cin >> value;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Некорректный ввод! Попробуйте снова: ";
		cin >> value;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Stack *create()
{
	Stack *stk = nullptr;
	string str;
	getline(cin, str);//читаем строку из потока ввода
	stringstream ss(str);//записываем строку в другой поток
	double value;
	while (!ss.eof())//извлекаем по одному значению до конца потока
	{
		ss >> value;
		if (ss.fail())
		{
			ss.clear();
			ss.ignore(1, '\n');
			continue;
		}
		push(value, &stk);//здесь создаем элемент
	}
	cout << "Введено: ";
	output(stk);
	return stk;
}

void push(double value, Stack **next)
{
	Stack *item = new Stack;
	item->value = value;
	item->next = *next;
	*next = item;
}

Stack *pop(Stack *stk)
{
	if (stk == nullptr) return nullptr;
	Stack *next = stk->next;//записали следующий элемент стека
	delete stk;//удалили элемент стека
	return next;
}

void output(Stack *stk)
{
	while (stk != nullptr)
	{
		cout << stk->value << " ";
		stk = stk->next;
	}
	cout << endl;
}

void clear(Stack *stk)
{
	Stack *next = nullptr;
	while (stk != nullptr)
	{
		next = stk->next;//записали следующий элемент стека
		delete stk;//удалили элемент стека
		stk = next;
	}
}
void process()
{
	Stack *first = create();
	Stack *stk = first;
	Stack *prev = nullptr;
	double amount = 0.0;
	int count = 0;
	while (stk != nullptr)
	{
		amount += stk->value;
		count++;
		stk = stk->next;
	}
	amount /= count;
	stk = first;//начинаем сначала
	first = nullptr;//сбрасываем, т.к. первый элемент после удаления может измениться
	while (stk != nullptr)
	{
		if (stk->value < amount)
		{
			if (prev != nullptr) prev->next = stk->next;
			stk = pop(stk);
		}
		else
		{
			if (prev == nullptr) first = stk;
			prev = stk;
			stk = stk->next;
		}
	}
	cout << "Результат: ";
	output(first);
	clear(first);
}

