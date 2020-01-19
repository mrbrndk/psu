/*
Дан список записей типа МАШИНА. Упорядочить список 
по любому из полей в любом направлении. Поле и 
направление выбирает пользователь. В функцию 
сортировки должен передаваться указатель на функцию 
сравнения двух элементов.

МАШИНА:
•	марка (строка 15 символов);
•	модель (строка 5 символов);
•	серийный номер (целое семизначное число);
•	год выпуска (целое четырехзначное число);
•	цвет (трехзначный целочисленный код)
*/

#include <stdio.h>
#include <string.h>
#include <locale.h>

typedef struct
{
	char name[16];
	char type[6];
	int number;
	int year;
	int color;
} Car;

int namecmp(Car val1, Car val2);
int typecmp(Car val1, Car val2);
int numbercmp(Car val1, Car val2);
int yearcmp(Car val1, Car val2);
int colorcmp(Car val1, Car val2);
void sort(Car *arr, unsigned n, unsigned dir, int (*cmp)(Car, Car));

int main(void)
{
	setlocale(LC_ALL, "Ru");
	unsigned n = 10;
	printf("Введите количество строк: ");
	do
	{
		scanf("%u", &n);
		if(n > 0) break;
		printf("Некорректный ввод! Попробуйте снова: ");
	} while(1);
	
	char input[50];
	Car car[n];/* = 		{	{ "Audi", 			"A6", 		4178385, 	2015, 	116 },//Audi A6 4178385 2015 116
								{ "Volkswagen", 	"Golf", 	8870107, 	1998, 	200 },//Volkswagen Golf 8870107 1998 200
								{ "Toyota", 		"Camry", 	3680869, 	2002, 	572 },//Toyota Camry 3680869 2002 572
								{ "Renault", 		"Logan", 	3786337, 	2011, 	787 },//Renault Logan 3786337 2011 787
								{ "Porsche", 		"911", 		4159903, 	2002, 	279 },//Porsche 911 4159903 2002 279
								{ "Peugeot", 		"406", 		6158368, 	2000, 	396 },//Peugeot 406 6158368 2000 396
								{ "Opel", 			"Corsa", 	4911784, 	2005, 	953 },//Opel Corsa 4911784 2005 953
								{ "Mitsubishi", 	"Magna", 	1377574, 	2005, 	881 },//Mitsubishi Magna 1377574 2005 881
								{ "Mazda", 			"Xedos", 	9231806, 	1991, 	912 },//Mazda Xedos 9231806 1991 912
								{ "BMW", 			"E92", 		9732223, 	2013, 	917 }//BMW E92 9732223 2013 917
							};*/
	fflush(stdin);
	printf("Введите строки с данными:\n");
	for(unsigned i = 0; i < n; i++) 
	{
		gets(input);
		if(sscanf(input, "%s %s %d %d %d", car[i].name, car[i].type, &car[i].number, &car[i].year, &car[i].color) != 5)
		{
			printf("Некорректный ввод! Попробуйте снова:\n");
			i--;
		}
	}

	unsigned col = 0, dir = 0;
	printf("\n0 - марка;\n1 - модель;\n2 - серийный номер;\n3 - год выпуска;\n4 - цвет.\n");
	printf("Выберите поле для сортировки: ");
	do
	{
		scanf("%u", &col);
		if(col < 5) break;
		printf("Некорректный ввод! Попробуйте снова: ");
	} while(1);
	printf("\n0 - прямая;\n1 - обратная.\n");
	printf("Выберите направление сортировки: ");
	do
	{
		scanf("%u", &dir);
		if(dir == 0 || dir == 1) break;
		printf("Некорректный ввод! Попробуйте снова: ");
	} while(1);

	int (*cmps[5]) (Car, Car) = { namecmp, typecmp, numbercmp, yearcmp, colorcmp };

	sort(car, n, dir, cmps[col]);
	printf("\nРезультат:\n");
	for(unsigned i = 0; i < n; i++) 
	{
		printf("%16s\t%6s\t%7d\t%4d\t%3d\n", car[i].name, car[i].type, car[i].number, car[i].year, car[i].color);
	}
	return 0;
}

void sort(Car *arr, unsigned n, unsigned dir, int (*cmp)(Car, Car))
{
	unsigned min;
	for (unsigned i = 0; i < n; i++)//сортировка по единице
	{
		min = i;
		for (unsigned j = i; j < n; j++)
		{
			if ((dir && cmp(arr[j], arr[min]) > 0) ||
				(!dir && cmp(arr[j], arr[min]) < 0)) min = j;// j and min
		}
		if (i != min)
		{
			Car flip = arr[i];
			arr[i] = arr[min];
			arr[min] = flip;
		}
	}
}
//функции сравнения элементов массива
int namecmp(Car val1, Car val2) { return strcmp(val1.name, val2.name); }
int typecmp(Car val1, Car val2) { return strcmp(val1.type, val2.type); }
int numbercmp(Car val1, Car val2) { return (val1.number - val2.number); }//если результат вычитания = 0: x1 == x2, < 0: x1 < x2; > 0: x1 > x2
int yearcmp(Car val1, Car val2) { return (val1.year - val2.year); }
int colorcmp(Car val1, Car val2) { return (val1.color - val2.color); }
