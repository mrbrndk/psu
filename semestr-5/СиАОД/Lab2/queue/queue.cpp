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
	bool value;
	Queue* next;
};

void get_value(int& value);
Queue* push(bool value, Queue* last);
Queue* pop(Queue* stk);
void output(Queue* stk);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (1)
	{
		int n = 0; // кол-во
		cout << "Введите количество: ";
		get_value(n); // ввод количества
		if (!n) break; // если ноль завершаем работу
		Queue* first = nullptr;
		Queue* last = nullptr;

		bool value;
		value = (n % 2 == 0) ? true : false; // задаем начальное значение
		for (int i = 0; i < n; i++)
		{
			value = (value) ? false : true; // по очередно выдаем карточки разного цвета
			last = push(value, last); // добавляем в конец очереди
			if (first == nullptr) first = last; // если первый элемент не задан - задаем
			if (i != n - 1) // если это не последняя карта
			{
				last = push(first->value, last); // добавляем в начало с конца
				first = pop(first); // с конца удаляем
			}
		}
		cout << "Результат: ";
		output(first); // выводим результат
		while(first != nullptr) first = pop(first); // очищаем
		cout << endl;
	}
	system("pause");
	return 0;
}

void get_value(int& value)
{ // ввод данных
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

Queue* push(bool value, Queue* last)
{ // добавить в конец
	Queue* item = new Queue;
	item->value = value;
	item->next = nullptr;
	if (last != nullptr) last->next = item;
	return item;
}

Queue* pop(Queue* stk)
{ // удалить
	if (stk == nullptr) return nullptr;
	Queue* item = stk->next;
	delete stk; // удалили элемент очереди
	return item;
}

void output(Queue* stk)
{ // вывод
	while (stk != nullptr)
	{
		cout << stk->value << " ";
		stk = stk->next;
	}
	cout << endl;
}