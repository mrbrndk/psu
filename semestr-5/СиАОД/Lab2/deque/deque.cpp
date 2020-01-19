#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>
#include <ctime>
using namespace std;

#if defined(max)
#undef max
#endif


struct Deque
{
	int value;
	Deque* next;
	Deque* prev;
};

template <typename T>
void get_value(T& value);
Deque* push_front(int value, Deque* first);
Deque* push_back(int value, Deque* last);
Deque* pop_front(Deque* stk);
Deque* pop_back(Deque* stk);
void output(Deque* stk);
int size(Deque* stk);
void clear(Deque* stk);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand((unsigned int)time(NULL));

	Deque* first = nullptr;
	Deque* last = nullptr;

	while (1)
	{
		cout << "Введите команду: ";
		string cmd;
		get_value(cmd);

		if (cmd == "push_front") // добавить элемент в начало
		{
			first = push_front(rand() % 10, first);
			if (last == nullptr) last = first; // если элемент добавлен, а последний элемент не задан
			 // значит был добавлен элемент дека, который является первым и последним
		}
		else if (cmd == "push_back") // добавить элемент в конец
		{
			last = push_back(rand() % 10, last);
			if (first == nullptr) first = last; // если элемент добавлен, а первый элемент не задан
			 // значит был добавлен элемент дека, который является первым и последним
		}
		else if (cmd == "pop_front") // удалить элемент в начале
		{
			first = pop_front(first);
			if (first == nullptr) last = first; // если элемент удален, и теперь первый элемент не задан
			 // значит был удален элемент дека, который являлся первым и последним
		}
		else if (cmd == "pop_back") // удалить элемент в конце
		{
			last = pop_back(last);
			if (last == nullptr) first = last; // если элемент удален, и теперь последний элемент не задан
			 // значит был удален элемент дека, который являлся первым и последним
		}
		else if (cmd == "front") // вывести первый элемент
		{
			if (first != nullptr) cout << first->value << endl;
			else cout << "error" << endl;
		}
		else if (cmd == "back") // вывести последний элемент
		{
			if (last != nullptr) cout << last->value << endl;
			else cout << "error" << endl;
		}
		else if (cmd == "clear") // очистить дек
		{
			clear(first);
			first = last = nullptr;
		}
		else if (cmd == "size") cout << size(first) << endl; // вывести размер дека
		else if (cmd == "output") output(first); // вывести содержимое
		else if (cmd == "exit") // завершить работу
		{
			cout << "BYE" << endl;
			break;
		}
		else cout << "Неверная команда!" << endl;
	}
	system("pause");
	return 0;
}

template <typename T>
void get_value(T& value)
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

Deque* push_front(int value, Deque* first)
{ // добавить элемент в начало
	Deque* item = new Deque;
	item->value = value;
	item->next = first;
	item->prev = nullptr;
	if (first != nullptr) first->prev = item;
	cout << "ok" << endl;
	return item;
}

Deque* push_back(int value, Deque* last)
{ // добавить элемент в конец
	Deque* item = new Deque;
	item->value = value;
	item->next = nullptr;
	item->prev = last;
	if (last != nullptr) last->next = item;
	cout << "ok" << endl;
	return item;
}

Deque* pop_front(Deque* stk)
{ // удалить элемент в начале
	if (stk == nullptr)
	{
		cout << "error" << endl;
		return nullptr;
	}
	Deque* first = stk->next;
	if (first != nullptr) first->prev = nullptr;
	cout << stk->value << endl;
	delete stk; // удалили элемент
	return first;
}

Deque* pop_back(Deque* stk)
{ // удалить элемент в конце
	if (stk == nullptr)
	{
		cout << "error" << endl;
		return nullptr;
	}
	Deque* last = stk->prev;
	if (last != nullptr) last->next = nullptr;
	cout << stk->value << endl;
	delete stk; // удалили элемент
	return last;
}

void output(Deque* stk)
{ // вывести содержмиое дека
	if (stk == nullptr) cout << "error";
	while (stk != nullptr)
	{
		cout << stk->value << " ";
		stk = stk->next;
	}
	cout << endl;
}

int size(Deque* stk)
{ // вывести размер дека
	int count = 0;
	Deque* next = nullptr;
	while (stk != nullptr)
	{
		next = stk->next;
		count++;
		stk = next;
	}
	return count;
}

void clear(Deque* stk)
{ // очистить дек
	Deque* next = nullptr;
	while (stk != nullptr)
	{
		next = stk->next; // записали следующий элемент
		delete stk; // удалили элемент
		stk = next;
	}
	cout << "ok" << endl;
}

