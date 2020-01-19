//1. АТД − множество с элементами типа char.Дополнительно перегрузить следующие операции :
//+− добавить элемент в множество(типа char + set);
//+− объединение множеств;
//== − проверка множеств на равенство.

//1. Выбрать класс АТД в соответствии с вариантом.
//2. Определить и реализовать в классе конструкторы, деструктор,
//функции Input(ввод с клавиатуры) и Print(вывод на экран), перегрузить
//операцию присваивания.
//3. Написать программу тестирования класса и выполнить тестирование.
//4. Дополнить определение класса заданными перегруженными операциями(в соответствии с вариантом).
//5. Реализовать эти операции.Выполнить тестирование.
//6. Реализовать вариант на языке С++ и(С# / Java на выбор).

#include <iostream>
using namespace std;

const int maxsize = 50;

class List
{
	private:
		char* first;
		int max;
		int size;
	public:
		List()
		{
			size = 0;
			max = maxsize;
			first = nullptr;
		}
		List(int value)
		{
			if (value > maxsize) value = maxsize;
			size = value;
			max = maxsize;
			first = new char[size + 1];
			init(first, size);
		}
		List(const List& obj)
		{
			size = obj.size;
			max = obj.max;
			first = new char[size + 1];
			init(first, size);
			for (int i = 0; i < size; i++)
				first[i] = obj.first[i];
		}
		~List()
		{
			delete[] first;
		}
		void input()
		{
			char value;
			cin >> value;
			add(value);
		}
		void output()
		{
			for (int i = 0; i < size; i++)
			{
				cout << first[i];
			}
			cout << endl;
		}
		List& operator = (const List& right)
		{
			resize(right.size, false);
			for (int i = 0; i < size; i++)
				first[i] = right.first[i];
			return *this;
		}
		friend List operator + (const char left, const List& right);
		friend List operator + (const List& left, const List& right);
		friend bool operator == (const List& left, const List& right);
	private :
		void init(char *arr, int size)//инициализация данных массива
		{
			for (int i = 0; i < size + 1; i++)
			{
				arr[i] = 0;
			}
		}
		void add(char item)//добавление элемента в новый большего размера массив
		{
			if (resize(size + 1, true))
				first[size - 1] = item;
		}
		bool resize(int value, bool savedata)
		{
			if (value > max) return false;
			char* tmp = new char[value + 1];
			init(tmp, value);
			if (savedata)
			{
				for (int i = 0; i < value - 1; i++)
					tmp[i] = first[i];
			}
			delete[] first;
			first = tmp;
			size = value;
			return true;
		}
};

List operator + (const char left, const List& right)
{
	List tmp(right.size + 1);
	for (int i = 0; i < right.size; i++)
		tmp.first[i] = right.first[i];
	tmp.first[right.size] = left;
	return tmp;
}

List operator + (const List& left, const List& right)
{
	List tmp(left.size + right.size);
	int oldsize = left.size;
	for (int i = 0; i < oldsize; i++)
		tmp.first[i] = left.first[i];
	for (int i = oldsize; i < tmp.size; i++)
		tmp.first[i] = right.first[i - oldsize];
	return tmp;
}

bool operator == (const List& left, const List& right)
{
	if (left.size != right.size) return false;
	for (int i = 0; i < left.size; i++)
		if (left.first[i] != right.first[i]) return false;
	return true;
}

int main()
{
    cout << "Hello World!\n";
	List obj1;
	for(int i = 0; i < 3; i++)
		obj1.input();
	obj1.output();

	List obj2;
	obj2 = obj1;
	List obj3;
	obj3 = obj1 + obj2;
	obj3.output();
	obj3 = 'f' + obj2;
	obj3.output();
	if (obj1 == obj2) cout << "obj1 == ob2" << endl;
	return 0;
}