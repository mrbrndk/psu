#include <iostream>
#include <string>
using namespace std;

class car
{
	private:
		string name;
		string model;
		string color;
		int weight;
		int maxspeed;
		int year;

	public:
		car()
		{
			cout << "constructor without param" << endl;
			name = "Unknown";
			model = "Unknown";
			color = "Unknown";
			weight = 0;
			maxspeed = 0;
			year = 1767;
		}
		car(string newname, string newmodel, string newcolor, int newweight, int newmaxspeed, int newyear)
		{
			cout << "constructor with param" << endl;
			name = newname;
			model = newmodel;
			color = newcolor;
			weight = newweight;
			maxspeed = newmaxspeed;
			year = newyear;
		}
		car(const car &newcar)
		{
			cout << "copy constructor" << endl;
			name = newcar.name;
			model = newcar.model;
			color = newcar.color;
			weight = newcar.weight;
			maxspeed = newcar.maxspeed;
			year = newcar.year;
		}
		~car()
		{
			cout << "destruct" << endl;
		}
		void getcar()
		{
			cout << "<< OUTPUT <<" << endl;
			cout << "NAME: " << name << endl;
			cout << "MODEL: " << model << endl;
			cout << "COLOR: " << color << endl;
			cout << "WEIGHT: " << weight << endl;
			cout << "MAXSPEED: " << maxspeed << endl;
			cout << "YEAR: " << year << endl;
		}
		void setcar()
		{
			cout << ">> INPUT >>" << endl;
			cout << "NAME: "; cin >> name;
			cout << "MODEL: "; cin >> model;
			cout << "COLOR: "; cin >> color;
			cout << "WEIGHT: "; cin >> weight;
			cout << "MAXSPEED: "; cin >> maxspeed;
			cout << "YEAR: "; cin >> year;
		}
};

int main()
{
	car obj1;
	obj1.getcar();
	obj1.setcar();
	car obj2("Tesla", "X", "Black", 3000, 300, 2017);
	obj2.getcar();
	car obj3(obj2);
	obj3.getcar();
	return 0;
}