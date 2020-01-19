#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <Windows.h>

using namespace std;

struct list
{
	int value;
	list* next;
	list(int k)
	{
		value = k;
		next = nullptr;
	}
};

list* push(list* p, int k);

struct node // структура для представления узлов дерева
{
	string key;
	unsigned height;
	int amount;
	list* line;
	node* left;
	node* right;
	node(string k, int l) // начальная инициализация
	{
		key = k;
		line = nullptr;
		line = push(line, l);
		left = right = nullptr;
		height = amount = 1;
	}
};

unsigned height(node* p) // возвращает высоту узла
{
	return p ? p->height : 0;
}

int bfactor(node* p) // возвращает разницу между высотами узлов потомков
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p) // исправляет высоту у узла
{
	unsigned hl = height(p->left);
	unsigned hr = height(p->right);
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

node* insert(node* p, string k, int l) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node(k, l); // создаем узел
	if (k < p->key) // если заданное значение меньше значения узла
		p->left = insert(p->left, k, l); // идем влево
	else
		p->right = insert(p->right, k, l); // идем вправо
	return balance(p);
}

node* find(node* p, string k) // поиск ключа k в дереве с корнем p
{
	if (!p) return nullptr; // если узла не существует
	if (p->key == k) return p;
	if (k < p->key) // если заданное значение меньше значения узла
		p = find(p->left, k); // идем влево
	else
		p = find(p->right, k); // идем вправо
	return p;
}

void traverse(node* p) // обходит все узлы дерева в порядке возрастания ключей
{
	if (!p) return;
	traverse(p->left);
	cout << setw(32) << p->key << " " << p->amount << ": ";
	while (p->line)
	{
		cout << (p->line)->value << " ";
		p->line = (p->line)->next;
	}
	cout << endl;
	traverse(p->right);
}

list* push(list* p, int k) // добавление элемента в список
{
	if(!p) return new list(k);
	list* item = new list(k);
	list* last = p;
	while (last->next != nullptr) last = last->next;
	last->next = item;
	return p;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream fin("input.txt", ios::in); // открываем файл для чтения
	if (!fin.is_open())
	{
		cout << "Произошла ошибка при открытии файла!" << endl;
		return 0;
	}

	node* tree = nullptr;
	string str;
	int line = 0;
	while (!fin.eof())
	{
		getline(fin, str); // читаем строку из потока ввода
		line++; // увеличиваем счетчик строк
		int i = 0;
		while (str[i])
		{
			str[i] = (char)tolower(str[i]); // делаем все символы строчными
			if((str[i] < 'a' || str[i] > 'z') && str[i] != ' ')
				str.erase(i, 1); // удаляем все символы кроме букв и пробелов
			else i++;
		}
		stringstream ss(str); // записываем строку в поток
		while (!ss.eof())
		{
			ss >> str; // читаем слово из потока
			node* item = find(tree, str);
			if (!item) // если узел с ключом str не найден
			{
				tree = insert(tree, str, line); // добавляем
			}
			else // если уже есть 
			{
				item->amount++; // увеличиваем счетчик
				item->line = push(item->line, line); // добавляем номер строки в список
			}
		}
	}
	traverse(tree); // обходим дерево от меньшего к большему и выводим 
	system("pause");
	return 0;
}