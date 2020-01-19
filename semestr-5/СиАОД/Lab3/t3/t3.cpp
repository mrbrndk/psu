#include <iostream>
#include <string>
#include <iomanip>
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
List* push(int number,  List* last);
void output(List* stk);
List* list_sort(List* first, bool dir);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	List* first = nullptr; // для сортируемого списка
	List* last = nullptr;
	List* afirst = nullptr; // для несортируемого списка
	List* alast = nullptr;

	int n;
	cout << "Введите количество чисел:" << endl;
	get_value(n);
	
	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++)
	{
		int randnum = rand() % 100; // записываем случайное число
		last = push(randnum, last); // добавляем в списки
		alast = push(randnum, alast);
		if (first == nullptr) first = last; // если не заданы - задаем
		if (afirst == nullptr) afirst = alast;
	}

	bool dir;
	cout << "Введите направление сортировки (1 - прямая, 0 - обратная):" << endl;
	get_value(dir); // получаем направление сортировки

	first = list_sort(first, dir); // сортируем
	output(first); // выводим полученный список

	bool archive;
	cout << "Хотите увидеть изначальный список? (1 - да, 0 - нет)" << endl;
	get_value(archive);
	if(archive) output(afirst); // если ответ положительный выводим несортированный список

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

List* push(int number, List* last)
{ // добавляет значения в список
	List* item = new List;
	item->number = number;
	item->next = nullptr;
	item->prev = last;
	if (last != nullptr) last->next = item;
	return item;
}

void output(List* stk)
{ // выводит список
	if (stk == nullptr) cout << "Список пуст!";
	while (stk != nullptr)
	{
		cout << stk->number << " ";
		stk = stk->next;
	}
	cout << endl;
}

List* list_sort(List* first, bool dir)
{ // сортирует список
	if (first == nullptr || first->next == nullptr) return first;
	 // если есть что сортировать
	List* i = first; // вспомогательный указатель
	while (i != nullptr)
	{
		int min = i->number; // записываем текущий элемент как минимальный
		List* min_value = i;
		List* j = i->next;
		while (j != nullptr)
		{
			int cur = j->number;
			if ((dir && cur < min) || (!dir && cur > min))
			{ // находим наименьший элемент и записываем в переменную
				min = cur;
				min_value = j;
			}
			j = j->next; // переходим к следующему элементу
		}
		if (min_value != i)
		{ // если значение минимального изменилось меняем местами
			List* flip_next = i->next;
			List* flip_prev = i->prev;

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

			if (min_value->prev == nullptr) first = min_value;
		}
		i = min_value->next; // переходим к следующему элементу
	}
	return first;
}