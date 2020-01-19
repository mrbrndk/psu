#include <iostream>
#include <iomanip>
#include <time.h>
#include <Windows.h>

using namespace std;

struct node // структура для представления узлов дерева
{
	char key;
	node* left;
	node* right;
	node(char k)
	{
		key = k;
		left = right = 0;
	}
};

node* insert(node* p, char k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return p;
}

node* removetree(node* p) // удалить дерево
{
	if (!p) return nullptr;
	p->left = removetree(p->left);
	p->right = removetree(p->right);
	delete p;
	return nullptr;
}

void print(node* p) // печать бинарного дерева
{
	if (!p) return;
	print(p->right);
	cout << p->key << " ";
	print(p->left);
}

bool IsVowel(char letter)
{ // возвращает true если гласный символ
	switch (letter)
	{
		case 'а': return true;
		case 'е': return true;
		case 'ё': return true;
		case 'и': return true;
		case 'о': return true;
		case 'у': return true;
		case 'ы': return true;
		case 'э': return true;
		case 'ю': return true;
		case 'я': return true;
		default: return false;
	}
	return false;
}

node* traverse(node* p)
{ // обходит дерево и если символ гласный удаляет правое поддерево
	if (!p) return nullptr;
	if (IsVowel(p->key)) p->right = removetree(p->right);
	p->left = traverse(p->left);
	p->right = traverse(p->right);
	return p;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	node* tree = nullptr;
	srand((unsigned)time(NULL) * 1000);
	for (int i = 0; i < 10; i++) // создаем дерево
		tree = insert(tree, rand() % 33 + 'а');
	print(tree); // выводим
	cout << endl << "-----------------------" << endl;
	tree = traverse(tree); // удаляем гласные и их правые поддеревья
	print(tree); // выводим итоговый результат
	cout << endl;
	system("pause");
	return 0;
}