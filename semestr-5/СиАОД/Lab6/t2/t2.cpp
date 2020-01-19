#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

struct list
{
	string value;
	int amount;
	list* next;
	list(string k)
	{
		value = k;
		amount = 1;
		next = nullptr;
	}
};

struct node // структура для представления узлов дерева
{
	int key; // кол-во жителей
	string country;
	string city;
	bool mark;
	unsigned char height;
	node* left;
	node* right;
	node(int k, string cou, string cit)
	{
		key = k;
		country = cou;
		city = cit;
		mark = false;
		left = right = 0;
		height = 1;
	}
};

unsigned char height(node* p) // возвращает высоту узла
{
	return p ? p->height : 0;
}

int bfactor(node* p) // возвращает разницу высот левого и правого поддеревьев
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p) // исправлет высоту узла
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node* insert(node* p, int k, string country, string city) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node(k, country, city);
	if (k < p->key)
		p->left = insert(p->left, k, country, city);
	else
		p->right = insert(p->right, k, country, city);
	return balance(p);
}

void print(node* p, bool m)
{ // вывод элементов с указанным значением метки
	if (!p) return;
	print(p->left, m);
	if(m == p->mark)
		cout << p->country << " " << p->city << " " << p->key << endl;
	print(p->right, m);
}

list* traverse(node* p, list* first) // ободит все узлы дерева в порядке возрастания ключей
{
	if (!p) return first;
	first = traverse(p->left, first);
	list* item = first;
	while (item != nullptr)
	{ // обходим список городов-миллиоников если такой город есть увеличиваем кол-во
		if (p->country == item->value)
		{
			if (p->key >= 1000000)
			{
				item->amount++;
				p->mark = true;
			}
			break;
		}
		item = item->next;
	}
	if (item == nullptr && p->key >= 1000000)
	{ // если город не найден в списке и при этом он миллионик 
		list* tmp = new list(p->country); // создаем элемент списка
		tmp->next = first;
		first = tmp;
		p->mark = true;
	}
	first = traverse(p->right, first);
	return first;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	node* tree = nullptr;
	int num = 0;
	cout << "Введите кол-во городов: ";
	cin >> num;
	for (int i = 0; i < num; i++)
	{ // создаем дерево городов
		string country, city;
		int population = 0;
		cout << "Введите название страны: ";
		cin >> country;
		cout << "Введите название города: ";
		cin >> city;
		cout << "Введите количество жителей: ";
		cin >> population;
		tree = insert(tree, population, country, city);
	}
		
	print(tree, false); // выводим все
	cout << endl;
	list* first = nullptr;
	first = traverse(tree, first); // выставляем метки и создаем список
	int maxamount = 0;
	string maxvalue;
	int total = 0;
	while (first != nullptr)
	{ // ищем наибольший 
		if (first->amount > maxamount)
		{
			maxamount = first->amount;
			maxvalue = first->value;
		}
		total += first->amount;
		first = first->next;
	}
	print(tree, true); // выводим с метками
	cout << endl;
	cout << "Всего городов-миллионников: " << total << endl;
	cout << "Страна с наибольшим кол-вом городов-миллионников: " << maxvalue << endl;
	system("pause");
	return 0;
}