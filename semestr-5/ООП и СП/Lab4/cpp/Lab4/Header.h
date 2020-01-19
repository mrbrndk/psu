#pragma once

#include <iostream>
using namespace std;

#if defined(max)
#undef max
#endif

const int maxsize = 50;

template <class T>
void get_value(T& value);

template <class T>
class List
{
	private:
		T* first;
		int max;
		int size;
	public:
		List();
		List(int value);
		List(const List<T>& obj);
		~List();
		void input();
		void print();
		List<T>& operator = (const List<T>& right);
		List<T> operator * (const List<T>& right);
		T& operator [] (int index);
	private:
		void init(T* arr, int size);//инициализация данных массива
		void add(T item);//добавление элемента в новый большего размера массив
		bool resize(int value, bool savedata);
};

class complex {
	int re; //действительная часть
	int im; // мнимая часть
	public:
		complex();
		complex(int r, int i);
		complex(const complex& obj);
		complex& operator = (const int& right);
		complex& operator = (const complex& right);
		complex operator * (const complex& right);
		int& operator [] (int index);
};

template <class T>
List<T>::List()
{
	size = 0;
	max = maxsize;
	first = nullptr;
}

template <class T>
List<T>::List(int value)
{
	if (value > maxsize) value = maxsize;
	size = value;
	max = maxsize;
	first = new T[size + 1];
	init(first, size);
}

template <class T>
List<T>::List(const List& obj)
{
	size = obj.size;
	max = obj.max;
	first = new T[size + 1];
	init(first, size);
	for (int i = 0; i < size; i++)
		first[i] = obj.first[i];
}

template <class T>
List<T>::~List()
{
	delete[] first;
}

template <class T>
void List<T>::input()
{
	T value;
	get_value(value);
	add(value);
}

template <>
void List<complex>::input()
{
	complex tmp;
	int val;
	get_value(val);
	tmp[0] = val;
	get_value(val);
	tmp[1] = val;
	add(tmp);
}

template <class T>
void List<T>::print()
{
	for (int i = 0; i < size; i++)
	{
		cout << first[i] << " ";
	}
	cout << endl;
}

template <>
void List<complex>::print()
{
	for (int i = 0; i < size; i++)
	{
		cout << first[i][0] << "+" << first[i][1] << "i" << " ";
	}
	cout << endl;
}

template <class T>
List<T>& List<T>::operator = (const List& right)
{
	resize(right.size, false);
	for (int i = 0; i < size; i++)
		first[i] = right.first[i];
	return *this;
}

template <class T>
List<T> List<T>::operator * (const List& right)
{
	List tmp((size < right.size) ? size : right.size);
	for (int i = 0; i < tmp.size; i++)
		tmp.first[i] = first[i] * right.first[i];
	return tmp;
}

template <class T>
T& List<T>::operator [] (int index)
{
	if (index > size) exit(1);
	return first[index];
}

template <class T>
void List<T>::init(T* arr, int size)//инициализация данных массива
{
	for (int i = 0; i < size + 1; i++)
	{
		arr[i] = 0;
	}
}

template <>
void List<complex>::add(complex item)//добавление элемента в новый большего размера массив
{//используем полную / явную специализацию шаблона функции
	if (resize(size + 1, true))
	{
		first[size - 1][0] = item[0];
		first[size - 1][1] = item[1];
	}
}

template <class T>
void List<T>::add(T item)//добавление элемента в новый большего размера массив
{
	if (resize(size + 1, true))
		first[size - 1] = item;
}

template <class T>
bool List<T>::resize(int value, bool savedata)
{
	if (value > max) return false;
	T* tmp = new T[value + 1];
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

complex::complex()
{
	re = 0;
	im = 0;
}

complex::complex(int r, int i)
{
	re = r;
	im = i;
}

complex::complex(const complex& obj)
{
	re = obj.re;
	im = obj.im;
}

complex& complex::operator = (const int& right)
{
	re = right;
	im = right;
	return *this;
}

complex& complex::operator = (const complex& right)
{
	re = right.re;
	im = right.im;
	return *this;
}

complex complex::operator * (const complex& right)
{
	complex tmp(re * right.re, im * right.im);
	return tmp;
}

int& complex::operator [] (int index)
{
	if (!index) return re;
	else return im;
}