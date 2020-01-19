#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

struct BinaryTree
{
	int Data; //поле данных
	BinaryTree* Left; //указатель на левый потомок
	BinaryTree* Right; // указатель на правый потомок
};

void Make_Binary_Tree(BinaryTree** Node, int n);
void Print_BinaryTree(BinaryTree* Node, int l);
void PreOrder_BinaryTree(BinaryTree* Node);
void PostOrder_BinaryTree(BinaryTree* Node);
void SymmetricOrder_BinaryTree(BinaryTree* Node);
void Insert_Node_BinaryTree(BinaryTree** Node, int Data);
void Delete_Node_BinaryTree(BinaryTree** Node, int Data);
bool Empty_BinaryTree(BinaryTree* Node);
void Delete_BinaryTree(BinaryTree** Node);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	BinaryTree* BTree = NULL;
	Make_Binary_Tree(&BTree, 7);//создаем дерево с семью элементами
	Print_BinaryTree(BTree, 1);//вывести дерево
	cout << endl << endl;
	PreOrder_BinaryTree(BTree);//обход дерева от меньшего к большему
	cout << endl << endl;
	PostOrder_BinaryTree(BTree);//обход дерева от большего к меньшему
	cout << endl << endl;
	SymmetricOrder_BinaryTree(BTree);//симметричный обход
	cout << endl << endl;
	Insert_Node_BinaryTree(&BTree, 10);//вставка вершины в бинарное дерево
	Delete_Node_BinaryTree(&BTree, 3);//удаление врешины из бинарного дерева
	PostOrder_BinaryTree(BTree);
	cout << endl << endl;
	cout << "Tree is empty? " << (Empty_BinaryTree(BTree)) << endl;//проверка дерева на пустоту
	Delete_BinaryTree(&BTree);//удаление бинарного дерева
	cout << "Tree is empty? " << (Empty_BinaryTree(BTree)) << endl;
	system("pause");
	return 0;
}

//создание бинарного дерева
void Make_Binary_Tree(BinaryTree** Node, int n)
{
	BinaryTree** ptr;//вспомогательный указатель
	srand((unsigned)time(NULL) * 1000);
	while (n > 0)
	{
		ptr = Node;
		while (*ptr != NULL)
		{
			if ((double)rand() / RAND_MAX < 0.5)
				ptr = &((*ptr)->Left);
			else ptr = &((*ptr)->Right);
		}
		(*ptr) = new BinaryTree();
		cout << "Введите значение ";
		cin >> (*ptr)->Data;
		n--;
	}
}

//печать бинарного дерева
void Print_BinaryTree(BinaryTree* Node, int l)
{
	int i;
	if (Node != NULL)
	{
		Print_BinaryTree(Node->Right, l + 1);
		for (i = 0; i < l; i++) cout << "    ";
		printf("%4ld", Node->Data);
		Print_BinaryTree(Node->Left, l + 1);
	}
	else cout << endl;
}

//прямой обход бинарного дерева
void PreOrder_BinaryTree(BinaryTree* Node)
{
	if (Node != NULL)
	{
		printf("%3ld", Node->Data);
		PreOrder_BinaryTree(Node->Left);
		PreOrder_BinaryTree(Node->Right);
	}
}

//обратный обход бинарного дерева
void PostOrder_BinaryTree(BinaryTree* Node)
{
	if (Node != NULL)
	{
		PostOrder_BinaryTree(Node->Left);
		PostOrder_BinaryTree(Node->Right);
		printf("%3ld", Node->Data);
	}
}

//симметричный обход бинарного дерева
void SymmetricOrder_BinaryTree(BinaryTree* Node)
{
	if (Node != NULL)
	{
		PostOrder_BinaryTree(Node->Left);
		printf("%3ld", Node->Data);
		PostOrder_BinaryTree(Node->Right);
	}
}

//вставка вершины в бинарное дерево
void Insert_Node_BinaryTree(BinaryTree** Node, int Data)
{
	BinaryTree* New_Node = new BinaryTree;
	New_Node->Data = Data;
	New_Node->Left = NULL;
	New_Node->Right = NULL;
	BinaryTree** ptr = Node;//вспомогательный указатель
	srand((unsigned)time(NULL) * 1000);
	while (*ptr != NULL)
	{
		double q = (double)rand() / RAND_MAX;
		if (q < 1 / 3.0) ptr = &((*ptr)->Left);
		else if (q > 2 / 3.0) ptr = &((*ptr)->Right);
		else break;
	}
	if (*ptr != NULL)
	{
		if ((double)rand() / RAND_MAX < 0.5)
			New_Node->Left = *ptr;
		else New_Node->Right = *ptr;
		*ptr = New_Node;
	}
	else
	{
		*ptr = New_Node;
	}
}

//удаление вершины из бинарного дерева
void Delete_Node_BinaryTree(BinaryTree** Node, int Data)
{
	if ((*Node) != NULL)
	{
		if ((*Node)->Data == Data)
		{
			BinaryTree* ptr = (*Node);
			if ((*Node)->Left == NULL && (*Node)->Right == NULL) (*Node) = NULL;
			else if ((*Node)->Left == NULL) (*Node) = ptr->Right;
			else if ((*Node)->Right == NULL) (*Node) = ptr->Left;
			else
			{
				(*Node) = ptr->Right;
				BinaryTree** ptr1;
				ptr1 = Node;
				while (*ptr1 != NULL)
					ptr1 = &((*ptr1)->Left);
				(*ptr1) = ptr->Left;
			}
			delete(ptr);
			Delete_Node_BinaryTree(Node, Data);
		}
		else
		{
			Delete_Node_BinaryTree(&((*Node)->Left), Data);
			Delete_Node_BinaryTree(&((*Node)->Right), Data);
		}
	}
}

//проверка пустоты бинарного дерева
bool Empty_BinaryTree(BinaryTree* Node)
{
	return (Node == NULL ? true : false);
}

//освобождение памяти, выделенной под бинарное дерево
void Delete_BinaryTree(BinaryTree** Node)
{
	if (*Node != NULL)
	{
		Delete_BinaryTree(&(*Node)->Left);
		Delete_BinaryTree(&(*Node)->Right);
		delete(*Node);
		*Node = NULL;
	}
}