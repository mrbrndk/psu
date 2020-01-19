/*
Разработать программу, в которой выполняется ввод списка 
записей определенного типа, а затем – обработка списка. 
Сначала в программе должен вводиться размер списка (целое число), 
а сам список создается в виде динамического массива структур. 
Ввод одной записи осуществляется в одной строке. 
При выполнении заданий высокой сложности (20 и 40 баллов) учитывать, 
что названия книг, наименования товаров, тексты сообщений, названия 
сеансов могут состоять из нескольких слов и заключаются в двойные кавычки. 
Направления всех сортировок указывает пользователь.

Вывести список на экран, упорядочив по единице измерения, 
а внутри каждой единицы измерения по наименованию товара.

ТОВАР:
•	наименование товара (строка 15 символов);
•	единицы измерения (строка 5 символов);
•	цена (вещественное число с двумя знаками после запятой);
•	количество (целое положительное число).

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

	printf("Введите количество строк списка: ");
	do
	{
		scanf("%u", &n);
		if(n > 1) break;
		printf("Недостаточное количество строк! Попробуйте снова: ");
	} while(1);

	struct Product prod[n];/* = {	{ "Молоко", 		"л", 		5.51, 	70 },//"Молоко" "л" 5,51 70
									{ "Мука", 			"кг", 		14.68, 	55 },//"Мука" "кг" 14,68 55
									{ "Манная крупа", 	"кг", 		7.32, 	35 },//"Манная крупа" "кг" 7,32 35
									{ "Мороженное", 	"гр", 		25.53, 	27 },//"Мороженное" "гр" 25,53 27
									{ "Курица замор.", 	"кг", 		61.69, 	49 },//"Курица замор." "кг" 61,69 49
									{ "Макароны", 		"гр", 		3.02, 	13 },//"Макароны" "гр" 3,02 13
									{ "Яйцо", 			"десят", 	1.89, 	90 },//"Яйцо" "десят" 1,89 90
									{ "Петрушка", 		"упак", 	5.78, 	74 },//"Петрушка" "упак" 5,78 74
									{ "Лимон", 			"шт", 		0.63, 	77 },//"Лимон" "шт" 0,63 77
									{ "Питьевая вода", 	"литр", 	2.86, 	39 }//"Питьевая вода" "литр" 2,86 39
								};*/

	char parse[4][16];
	printf("Введите строки с данными:\n");
	fflush(stdin);
	for (unsigned i = 0; i < n; i++)//ввод и парсинг
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
		if(start < 4) i--;//что-то не прочитано
		start = 0;
		strcpy(prod[i].name, parse[0]);
		strcpy(prod[i].unit, parse[1]);
		prod[i].price = atof(parse[2]);
		prod[i].amount = atoi(parse[3]);
	}

	printf("\nНаправления сортировки:\n0 - А-Я;\n1 - Я-А.\n\n");
	printf("Выберите направление сортировки для единиц измерения: ");
	scanf("%u", &sortunit);

	printf("Выберите направление сортировки для наименований товаров: ");
	scanf("%u", &sortname);

	for (unsigned i = 0; i < n; i++)//сортировка по единице
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
	for (unsigned i = 1; i < n + 1; i++)//сортировка по алфавиту
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
	printf("\n\n%15s\t%5s\t%s\t%6s\n", "Наименование", "Ед.", "Цена", "Кол-во");
	for (unsigned i = 0; i < n; i++) printf("%15s\t%5s\t%.2f\t%6u\n", prod[i].name, prod[i].unit, prod[i].price, prod[i].amount);
	return 0;
}
