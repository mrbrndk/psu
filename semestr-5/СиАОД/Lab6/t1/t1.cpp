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

unsigned char height(node* p) // возвращает высоту узла если он существует
{
	return p ? p->height : 0;
}

int bfactor(node* p) // возвращает разницу высот левого и правого поддерва
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p) // исправляет высоту узла
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

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findmin(p->left) : p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->key) // двигаем указатель строну указанного значения
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p; // удаляем элемент
		if (!r) return q; // елси правого нет, возвращаем левый
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

void print(node* p) // вывод
{
	if (!p) return;
	print(p->left);
	cout << " " << p->key << " ";
	print(p->right);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	node* tree = nullptr;
	int num = 0;
	cout << "Enter the number of elements in the Tree" << endl;
	cin >> num;
	cout << " == Result == ";
	srand((unsigned)time(NULL) * 1000);
	for (int i = 0; i < num; i++) // создаем дерево с случайными значениями
		tree = insert(tree, rand() % 100);
	print(tree); // вывод
	cout << endl;
	cout << "input number top for delete" << endl;
	cin >> num;
	remove(tree, num); // удаляем указанный
	cout << " == Result after delete == ";
	print(tree); // вывод
	cout << endl;
	system("pause");
	return 0;
}