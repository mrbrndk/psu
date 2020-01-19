#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

struct node // структура для представления узлов дерева
{
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};

unsigned char height(node* p)
{ // если существует, возвращает высоту
	return p ? p->height : 0;
}

int bfactor(node* p)
{ // возвращает разницу между высотой правой и левой ветки
	return height(p->right) - height(p->left);
}

void fixheight(node* p)
{ // исправляет высоту у родителя, при правильно установленных высотах у потомков
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

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

int traverse(node* p, int lvl)
{ // обходит дерево и возвращает кол-во четных узлов
	if (!p) return 0;
	int amount = 0;
	amount += traverse(p->left, lvl + 1);
	amount += traverse(p->right, lvl + 1);
	if (!(p->key % 2)) // когда остаток от деления ноль
	{
		cout << "value: " << p->key << "; level:" << lvl << endl;
		amount++;
	}
	return amount;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand((unsigned)time(NULL));
	node* tree = nullptr;
	for (int i = 0; i < 10; i++) // создаем дерево из 10 элементов
		tree = insert(tree, rand() % 100); // с случайными значениями
	int amount = traverse(tree, 1); // записываем ко-во четных узлов
	cout << "Кол-во четных чисел: " << amount << endl;
	system("pause");
	return 0;
}