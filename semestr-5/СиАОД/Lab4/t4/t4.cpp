#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>

#if defined(max)
#undef max
#endif

using namespace std;

struct node
{
	string Name; //поля данных
	int Number = 0;
	int Tariff = 0;
	node* Left = nullptr; //указатель на левый потомок
	node* Right = nullptr; // указатель на правый потомок
};

struct List
{
	int value = 0;
	int amount = 0;
	List* next = nullptr;
};

template <typename T>
void get_value(T& value);
void make(node** p, int n);
void print(node* p, int l);
void number(node* p, int value);
void calculate(node* p, List** first);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	node* BTree = nullptr;
	make(&BTree, 5);
	print(BTree, 1);
	cout << "Введите номер: ";
	int num;
	get_value(num);
	number(BTree, num);
	List* first = nullptr;
	calculate(BTree, &first);
	List* max = new List;
	while (first != nullptr)
	{
		if (first->amount > max->amount)
		{
			max->amount = first->amount;
			max->value = first->value;
		}
		first = first->next;
	}
	cout << "Самый полярный тариф: " << max->value << endl;
	system("pause");
	return 0;
}

template <typename T>
void get_value(T& value)
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

//создание бинарного дерева
void make(node** p, int n)
{
	node** ptr;//вспомогательный указатель
	while (n > 0)
	{
		node* tmp = new node();
		cout << "Введите ФИО: ";
		get_value(tmp->Name);
		cout << "Введите номер: ";
		get_value(tmp->Number);
		cout << "Введите код тарифа: ";
		get_value(tmp->Tariff);
		ptr = p;
		while (*ptr != nullptr)
		{
			if (tmp->Number < (*ptr)->Number)
				ptr = &((*ptr)->Left);
			else ptr = &((*ptr)->Right);
		}
		(*ptr) = tmp;
		n--;
	}
}

//печать бинарного дерева
void print(node* p, int l)
{
	if (p != nullptr)
	{
		print(p->Right, l + 1);
		cout << p->Name << " " << p->Number << " " << p->Tariff << endl;
		print(p->Left, l + 1);
	}
}

//поиск номера прямым обходом бинарного дерева
void number(node* p, int value)
{
	if (p != nullptr)
	{
		if (p->Number == value)
		{
			cout << p->Name << " " << p->Number << " " << p->Tariff << endl;
			return;
		}
		else
		{
			if(value < p->Number) number(p->Left, value);
			else number(p->Right, value);
		}
	}
}

void calculate(node* p, List** first)
{
	if (p != nullptr)
	{
		List* item = *first;
		while (item != nullptr)
		{
			if (p->Tariff == item->value)
			{
				item->amount++;
				break;
			}
			item = item->next;
		}
		if (item == nullptr)
		{
			List* tmp = new List;
			tmp->value = p->Tariff;
			tmp->amount = 1;
			tmp->next = *first;
			*first = tmp;
		}
		calculate(p->Left, first);
		calculate(p->Right, first);
	}
}