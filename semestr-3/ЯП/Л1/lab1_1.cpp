#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>
using namespace std;

#if defined(max)
#undef max
#endif

struct Queue
{
	int value;
	Queue *next;
};

template <typename T>
void get_value(T &value);
Queue *create();
Queue *push(int value, Queue *last);
Queue *pop(Queue *stk, Queue *prev);
void output(Queue *stk);
void clear(Queue *stk);
void process();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int n = 0;//кол-во очередей для обработки
	cout << "Введите количество очередей для обработки: ";
	get_value(n);
	
	cout << "Введите значения элементов очереди через пробел:" << endl;
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

Queue *create()
{
	Queue *first = nullptr;
	Queue *last = nullptr;
	string str;
	getline(cin, str);//читаем строку из потока ввода
	stringstream ss(str);//записываем строку в другой поток
	int value;
	while(!ss.eof())//извлекаем по одному значению до конца потока
	{
		ss >> value;
		if (ss.fail())
		{
			ss.clear();
			ss.ignore(1, '\n');
			continue;
		}
		last = push(value, last);//здесь создаем элемент
		if (first == nullptr) first = last;
	}
	cout << "Введено: ";
	output(first);
	return first;
}

Queue *push(int value, Queue *last)
{
	Queue *item = new Queue;
	item->value = value;
	item->next = nullptr;
	if(last != nullptr) last->next = item;
	return item;
}

Queue *pop(Queue *stk, Queue *prev)
{
	if (stk == nullptr) return nullptr;
	if (prev != nullptr) prev->next = stk->next;
	delete stk;//удалили элемент очереди
	return prev;
}

void output(Queue *stk)
{
	while(stk != nullptr)
	{
		cout << stk->value << " ";
		stk = stk->next;
	}
	cout << endl;
}

void clear(Queue *stk)
{
	Queue *next = nullptr;
	while (stk != nullptr)
	{
		next = stk->next;//записали следующий элемент очереди
		delete stk;//удалили элемент очереди
		stk = next;
	}
}
void process()
{
	Queue *stk = create();
	Queue *first = nullptr;
	Queue *next = nullptr;
	Queue *prev = nullptr;

	while (stk != nullptr)
	{
		if (stk->value % 2 == 0)
		{
			next = stk->next;
			prev = pop(stk, prev);
			stk = next;
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

