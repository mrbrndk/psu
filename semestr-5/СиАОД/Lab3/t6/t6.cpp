#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>
using namespace std;

#if defined(max)
#undef max
#endif

struct PhoneBook
{
	string lastname;
	string firstname;
	string middlename;
	int number = 0;
	PhoneBook* next = nullptr;
	PhoneBook* prev = nullptr;
};

struct List
{
	string lastname;
	string firstname;
	string middlename;
	int number = 0;
	List* next = nullptr;
};

template <class T>
bool get_value(stringstream& ss, T& value);
template <class T>
T* push(string lastname, string firstname, string middlename, int number, T* last);
template <>
PhoneBook* push(string lastname, string firstname, string middlename, int number, PhoneBook* last);
template <class T>
void output(T* stk);
void sort(PhoneBook** first, PhoneBook** last);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	PhoneBook* first = nullptr;
	PhoneBook* last = nullptr;

	 // заполняем список данными
	first = last = push("Сидоров", "Сидр", "Сидрович", 7319455, last);
	last = push("Иванов", "Иван", "Иванович", 4553465, last);
	last = push("Петров", "Петр", "Петрович", 1563556, last);
	last = push("Лапин", "Гавриил", "Васильевич", 907, last);
	last = push("Соболев", "Геннадий", "Леонидович", 5431426, last);
	last = push("Фомичёв", "Владислав", "Николаевич", 5667018, last);
	last = push("Горшков", "Даниил", "Тимурович", 769, last);
	last = push("Доронин", "Богдан", "Семёнович", 1515241, last);
	last = push("Анисимов", "Леонид", "Николаевич", 1035593, last);
	last = push("Лихачёв", "Юрий", "Витальевич", 4208039, last);

	output(first); // выводим двунаправленный список
	sort(&first, &last); // сортируем его

	PhoneBook* stk = last;
	List* l_first = nullptr;
	List* l_last = nullptr;
	while (stk != nullptr)
	{
		if (stk->number >= 1000)
		{ // в созданный однонаправленный список добавляем элементы с номерами больше трехзначных
			l_last = push(stk->lastname, stk->firstname, stk->middlename, stk->number, l_last);
			if (l_first == nullptr) l_first = l_last; // если не задан - задаем
		}
		stk = stk->prev; // двигаемся от конца к началу
	}
	output(l_first); // выводим результат
	system("pause");
	return 0;
}

template <class T>
bool get_value(stringstream& ss, T& value)
{ // ввод данных
	ss >> value;
	if (ss.fail())
	{
		ss.clear();
		ss.ignore(1, '\n');
		cout << "Некорректный ввод! Попробуйте снова: ";
		return false;
	}
	return true;
}

template <class T>
T* push(string lastname, string firstname, string middlename, int number, T* last)
{ // добавление в список
	T* item = new T;
	item->lastname = lastname;
	item->firstname = firstname;
	item->middlename = middlename;
	item->number = number;
	item->next = nullptr;
	if (last != nullptr) last->next = item;
	return item;
}

template <>
PhoneBook* push(string lastname, string firstname, string middlename, int number, PhoneBook* last)
{ // добавление в двунаправленный список
	PhoneBook* item = new PhoneBook;
	item->lastname = lastname;
	item->firstname = firstname;
	item->middlename = middlename;
	item->number = number;
	item->next = nullptr;
	item->prev = last;
	if (last != nullptr) last->next = item;
	return item;
}

template <class T>
void output(T* stk)
{ // вывод
	if (stk == nullptr) cout << "Список пуст!";
	while (stk != nullptr)
	{
		cout << stk->lastname << " " << stk->firstname << " " << stk->middlename << " " << stk->number << endl;
		stk = stk->next;
	}
	cout << endl;
}

void sort(PhoneBook** first, PhoneBook** last)
{ // сортировка
	if (*first == nullptr || (*first)->next == nullptr) return;

	PhoneBook* i = *first; // вспомогательный указатель
	while (i != nullptr)
	{
		string min_str = i->lastname + i->firstname + i->middlename;
		PhoneBook* min_value = i; // записываем текущий элемент как минимальный
		PhoneBook* j = i->next;
		while (j != nullptr)
		{
			string cur_str = j->lastname + j->firstname + j->middlename;
			if (cur_str < min_str)
			{ // находим наименьший элемент и записываем в переменную
				min_str = cur_str;
				min_value = j;
			}
			j = j->next; // переходим к следующему элементу
		}
		if (min_value != i)
		{ // если значение минимального изменилось - меняем местами
			PhoneBook* flip_next = i->next;
			PhoneBook* flip_prev = i->prev;

			if (i->next == min_value)
			{ // если у текущего элемента следующий тот, с кем обмен (соседи)
				flip_next = i;
				min_value->prev = min_value;
			}

			i->next = min_value->next;
			i->prev = min_value->prev;
			if (i->next != nullptr) (i->next)->prev = i;
			if (i->prev != nullptr) (i->prev)->next = i;
			 // если предыдущий элемент существует, то устанавливаем значение указателя next у предыдущего элемента на текущий

			min_value->next = flip_next;
			min_value->prev = flip_prev;
			if (min_value->next != nullptr) (min_value->next)->prev = min_value;
			if (min_value->prev != nullptr) (min_value->prev)->next = min_value;

		}
		if (min_value->prev == nullptr) *first = min_value;
		if (min_value->next == nullptr) *last = min_value;
		i = min_value->next; // переходим к следующему элементу
	}
}