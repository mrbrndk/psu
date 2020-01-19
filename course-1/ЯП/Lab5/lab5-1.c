/*
����������� ���������, � ������� ����������� ���� ������ 
������� ������������� ����, � ����� � ��������� ������. 
������� � ��������� ������ ��������� ������ ������ (����� �����), 
� ��� ������ ��������� � ���� ������������� ������� ��������. 
���� ����� ������ �������������� � ����� ������. 
��� ���������� ������� ������� ��������� (20 � 40 ������) ���������, 
��� �������� ����, ������������ �������, ������ ���������, �������� 
������� ����� �������� �� ���������� ���� � ����������� � ������� �������. 
����������� ���� ���������� ��������� ������������.

������� ������ �� �����, ���������� �� ������� ���������, 
� ������ ������ ������� ��������� �� ������������ ������.

�����:
�	������������ ������ (������ 15 ��������);
�	������� ��������� (������ 5 ��������);
�	���� (������������ ����� � ����� ������� ����� �������);
�	���������� (����� ������������� �����).

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct Product
{
	char name[16];
	char unit[6];
	float price;
	unsigned amount;
};

int main(void)
{
	setlocale(LC_ALL, "Ru");
	char input[51];
	unsigned n, sortname = 0, sortunit = 0, min = 0, start = 0;

	printf("������� ���������� ����� ������: ");
	do
	{
		scanf("%u", &n);
		if(n > 1) break;
		printf("������������� ���������� �����! ���������� �����: ");
	} while(1);

	struct Product prod[n];/* = {	{ "������", 		"�", 		5.51, 	70 },//"������" "�" 5,51 70
									{ "����", 			"��", 		14.68, 	55 },//"����" "��" 14,68 55
									{ "������ �����", 	"��", 		7.32, 	35 },//"������ �����" "��" 7,32 35
									{ "����������", 	"��", 		25.53, 	27 },//"����������" "��" 25,53 27
									{ "������ �����.", 	"��", 		61.69, 	49 },//"������ �����." "��" 61,69 49
									{ "��������", 		"��", 		3.02, 	13 },//"��������" "��" 3,02 13
									{ "����", 			"�����", 	1.89, 	90 },//"����" "�����" 1,89 90
									{ "��������", 		"����", 	5.78, 	74 },//"��������" "����" 5,78 74
									{ "�����", 			"��", 		0.63, 	77 },//"�����" "��" 0,63 77
									{ "�������� ����", 	"����", 	2.86, 	39 }//"�������� ����" "����" 2,86 39
								};*/

	char parse[4][16];
	printf("������� ������ � �������:\n");
	fflush(stdin);
	for (unsigned i = 0; i < n; i++)//���� � �������
	{
		printf("%d: ", i + 1);
		gets(input);
		char *ptr = strtok(input, "\"");
		while(ptr != NULL && start < 4)
		{
			strcpy(parse[start], ptr);
			ptr = (start > 1) ? strtok(NULL, "\"") : strtok(NULL, " \"");
			start++;
		}
		if(start < 4) i--;//���-�� �� ���������
		start = 0;
		strcpy(prod[i].name, parse[0]);
		strcpy(prod[i].unit, parse[1]);
		prod[i].price = atof(parse[2]);
		prod[i].amount = atoi(parse[3]);
	}

	printf("\n����������� ����������:\n0 - �-�;\n1 - �-�.\n\n");
	printf("�������� ����������� ���������� ��� ������ ���������: ");
	scanf("%u", &sortunit);

	printf("�������� ����������� ���������� ��� ������������ �������: ");
	scanf("%u", &sortname);

	for (unsigned i = 0; i < n; i++)//���������� �� �������
	{
		min = i; 
		for (unsigned j = i; j < n; j++)
		{
			if ((!sortunit && strcmp(prod[j].unit, prod[min].unit) < 0) || 
				(sortunit && strcmp(prod[j].unit, prod[min].unit) > 0)) min = j;
		}
		if (i != min)
		{
			struct Product flip;
			flip = prod[i];
			prod[i] = prod[min];
			prod[min] = flip;
		}
	}
	min = 0;
	for (unsigned i = 1; i < n + 1; i++)//���������� �� ��������
	{
		if(strcmp(prod[i].unit, prod[i - 1].unit) != 0)
		{
			for (unsigned j = start; j < i; j++)
			{
				min = j;
				for (unsigned k = j; k < i; k++) 
				{
					if ((!sortname && strcmp(prod[k].name, prod[min].name) < 0) || 
						(sortname && strcmp(prod[k].name, prod[min].name) > 0)) min = k;
				}
				if (j != min)
				{
					struct Product flip;
					flip = prod[j];
					prod[j] = prod[min];
					prod[min] = flip;
				}
			}
			start = i;
		}
	}
	printf("\n\n%15s\t%5s\t%s\t%6s\n", "������������", "��.", "����", "���-��");
	for (unsigned i = 0; i < n; i++) printf("%15s\t%5s\t%.2f\t%6u\n", prod[i].name, prod[i].unit, prod[i].price, prod[i].amount);
	return 0;
}
