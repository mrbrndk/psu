//1. Определить иерархию классов(в соответствии с вариантом).
//2. Определить в классе статическую компоненту - указатель на начало связанного списка объектов и статическую функцию для просмотра
//списка.
//3. Реализовать классы.
//4. Написать демонстрационную программу, в которой создаются
//объекты различных классов и помещаются в список, после чего список
//просматривается.
//5. Сделать соответствующие методы не виртуальными и посмотреть,
//что будет.
//6. Реализовать аналог на языке С# и Java.

#include <iostream>

using namespace std;

class Person
{
	private:
		string name;
	public:
		static Person* first;
		static Person* last;
		Person* next;
		Person()
		{
			next = nullptr;
			if (first == nullptr) first = this;
			if (last != nullptr) last->next = this;
			last = this;

			name = "Vladimir";
		}
		static void print()
		{
			Person *i = first;
			while (i != nullptr)
			{
				i->show();
				i = i->next;
			}
		}
		virtual void show()
		{
			cout << "Name: " << name << endl;
		}
};

class Student : public Person
{
	private:
		string name;
		int age;
		int course;
	public:
		Student() : Person()
		{
			name = "Viktor";
			age = 22;
			course = 2;
		}
		void show()
		{
			cout << "Name: " << name << "; ";
			cout << "Age: " << age << "; ";
			cout << "Course: " << course << endl;
		}
};

class Teacher : public Person
{
	private:
		string name;
		int age;
		int experience;
	public:
		Teacher() : Person()
		{
			name = "Olga";
			age = 35;
			experience = 15;
		}
		void show()
		{
			cout << "Name: " << name << "; ";
			cout << "Age: " << age << "; ";
			cout << "Experience: " << experience << endl;
		}
};

class Head : public Person
{
	private:
		string name;
		int age;
		bool secondment;
	public:
		Head() : Person()
		{
			name = "Alexey";
			age = 47;
			secondment = true;
		}
		void show()
		{
			cout << "Name: " << name << "; ";
			cout << "Age: " << age << "; ";
			cout << "Secondment: " << secondment << endl;
		}
};

Person* Person::first;
Person* Person::last;

int main()
{
	Person::first = nullptr;
	Person::last = nullptr;

	Person obj1;
	Student obj2;
	Teacher obj3;
	Head obj4;
	obj4.print();
	return 0;
}
