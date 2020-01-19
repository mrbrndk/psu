#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

struct node // структура для представления узлов дерева
{
	int key;
	unsigned height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = nullptr; height = 1; }
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

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node(k); // создаем узел
	if (k < p->key) // если вставляемое значение меньше ключ текущего узла 
		p->left = insert(p->left, k); // идем влево
	else
		p->right = insert(p->right, k); // иначе идем вправо
	return balance(p); // возвращаем сбалансированное дерево
}

int sum(node* p, int l) // возвращает сумму значений уровня l
{
	if (!p) return 0;
	if (l == 1) return p->key;
	int val = 0;
	val += sum(p->left, l - 1);
	val += sum(p->right, l - 1);
	return val;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	node* tree = nullptr;
	int val = 0;
	for (int i = 1; i < 16; i++)
	{ // создаем дерево
		cout << "Введите значение: ";
		cin >> val;
		tree = insert(tree, i);
	}
	cout << "Введите уровень: ";
	cin >> val;
	val = sum(tree, val); // считаем и записывает сумму узлов на указанном уровне
	cout << "Сумма: " << val << endl;
	system("pause");
	return 0;
}