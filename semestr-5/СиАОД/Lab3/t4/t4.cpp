#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

#if defined(max)
#undef max
#endif

struct List
{
	int number = 0;
	List* next = nullptr;
	List* prev = nullptr;
};

template <typename T>
void get_value(T& value);
List* push(int number, List* last);
List* pop(List* stk);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	List* first = nullptr;
	List* last = nullptr;
	List* stk = nullptr;

	cout << "Введите значение k: ";
	int n = 64, k = 0;
	get_value(k);//вводим значение

	for (int i = 1; i <= 64; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			last = push(j, last);//добавляем в список участников
			if (last != nullptr)
			{
				if (first == nullptr) first = last;//если не задан - задаем
				first->prev = last;
				last->next = first;//закольцовываем список
			}
		}
		cout << i << ":";

		stk = first;
		int count = 0;
		while (stk != nullptr)
		{
			count++;
			if (count == k)
			{//когда достигли заданного значения k
				count = 0;//первый т.к pop вернет указатель на следующий
				if (stk == stk->next)
				{//если остался только один участник
					stk->next = nullptr;//раскольцовываем список
					cout << " - " << stk->number << endl;
				}
				stk = pop(stk);//удаляем из списка участников
			}
			else stk = stk->next;//перемещаем указатель на следующего
		}
		first = last = nullptr;
	}
	system("pause");
	return 0;
}

template <typename T>
void get_value(T& value)
{//ввод данных
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

List* push(int number, List* last)
{//добавить элемент в список
	List* item = new List;
	item->number = number;
	item->next = nullptr;
	item->prev = last;
	if (last != nullptr) last->next = item;
	return item;
}

List* pop(List* stk)
{//удалить элемент из списка
	if (stk == nullptr) return nullptr;
	List* next = stk->next;
	List* prev = stk->prev;
	if (next != nullptr) next->prev = prev;
	if (prev != nullptr) prev->next = next;
	delete stk;//удалили элемент
	return next;
}