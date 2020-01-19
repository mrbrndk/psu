#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

#if defined(max)
#undef max
#endif

struct List
{
	string lastname;
	string firstname;
	string middlename;
	string number;
	List* next = nullptr;
};

template <typename T>
void get_value(T& value);
List* push(string lastname, string firstname, string middlename, string number, List* last);
List* search_name(List* stk, string value);
List* search_number(List* stk, string value);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	List* first = nullptr;
	List* last = nullptr;

	 // заполняем список данными
	first = last = push("Сидоров", "Сидр", "Сидрович", "7315955", last);
	last = push("Иванов", "Иван", "Иванович", "4543465", last);
	last = push("Петров", "Петр", "Петрович", "1566556", last);
	last = push("Лапин", "Гавриил", "Васильевич", "7937907", last);
	last = push("Соболев", "Геннадий", "Леонидович", "5231426", last);
	last = push("Фомичёв", "Владислав", "Николаевич", "5607018", last);
	last = push("Горшков", "Даниил", "Тимурович", "6836569", last);
	last = push("Доронин", "Богдан", "Семёнович", "1517241", last);
	last = push("Анисимов", "Леонид", "Николаевич", "1059593", last);
	last = push("Лихачёв", "Юрий", "Витальевич", "4208139", last);

	cout << "Введите данные для поиска, по завершении ввода введите пустую строку:" << endl;
	string str;
	while (1)
	{
		getline(cin, str); // читаем строку из потока ввода
		if (str.empty()) break; // если строка пустая завершаем ввод
		List* result = nullptr;
		result = search_name(first, str); // ищем по имени
		if (result != nullptr) cout << result->lastname << endl << endl; // если что-либо найдено - выводим
		else
		{ // если по имени не найдено - ищем по номеру
			result = search_number(first, str);
			if (result != nullptr) cout << result->number << endl << endl; // если что-либо найдено - выводим
		}
		if (result == nullptr) cout << "Ничего не найдено!" << endl << endl; // если ничего не нашлось - выводим ошибку
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

List* push(string lastname, string firstname, string middlename, string number, List* last)
{ // добавление в список
	List* item = new List;
	item->lastname = lastname;
	item->firstname = firstname;
	item->middlename = middlename;
	item->number = number;
	item->next = nullptr;
	if (last != nullptr) last->next = item;
	return item;
}

List* search_name(List* stk, string value)
{ // поиск по имени
	if (stk == nullptr) return nullptr;
	while (stk != nullptr)
	{
		if (stk->number == value) return stk;
		stk = stk->next;
	}
	return nullptr;
}

List* search_number(List* stk, string value)
{ // поиск по номеру
	if (stk == nullptr) return nullptr;
	while (stk != nullptr)
	{
		if (stk->lastname == value) return stk;
		stk = stk->next;
	}
	return nullptr;
}