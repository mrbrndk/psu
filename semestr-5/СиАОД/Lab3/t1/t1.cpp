#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

#if defined(max)
#undef max
#endif

struct Queue
{
	string word;
	int amount = 0;
	Queue* next = nullptr;
};

template <typename T>
void get_value(T& value);
bool search_word(Queue** stk, string word);
Queue* push(string value, Queue* last);
void output(Queue* stk);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream fin("input.txt", ios::in);//открываем файл для чтения
	if (!fin.is_open())
	{
		cout << "Произошла ошибка при открытии файла!" << endl;
		return 0;
	}

	Queue* first = nullptr;
	Queue* last = nullptr;
	string str;
	while (!fin.eof())
	{
		fin >> str;
		int i = 0;
		while (str[i])//обходим символы в строке
		{
			str[i] = (char)tolower(str[i]);//меняем все символы на строчные
			if ((str[i] < 'a' || str[i] > 'z') && str[i] != ' ')
				str.erase(i, 1);//удаляем все символы кроме букв и пробелов
			else i++;
		}
		Queue* stk = first;
		if (search_word(&stk, str)) stk->amount++;//если слово есть в списке - увеличиваем их кол-во
		else
		{//иначе добавляем в список
			last = push(str, last);
			if (first == nullptr) first = last;//если не задан - задаем
		}
	}
	output(first);//выводим результат
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

bool search_word(Queue** stk, string word)
{//ищет заданные слова в списке
	while (*stk != nullptr)
	{
		if ((*stk)->word == word) return true;
		*stk = (*stk)->next;
	}
	return false;
}

Queue* push(string value, Queue* last)
{//добавляет новый элемент
	Queue* item = new Queue;
	item->word = value;
	item->amount = 1;
	item->next = nullptr;
	if (last != nullptr) last->next = item;
	return item;
}

void output(Queue* stk)
{//вывод результата
	while (stk != nullptr)
	{
		cout << stk->word << " : " << stk->amount << endl;
		stk = stk->next;
	}
	cout << endl;
}