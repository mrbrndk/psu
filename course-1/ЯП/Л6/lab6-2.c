/*
При реализации функции использовать механизм 
передачи параметров по ссылке. В основной 
функции main реализовать демонстрацию работы 
разработанной пользовательской функции. Ввод 
и вывод всех данных осуществляется в функции main.

Реализовать функцию преобразования строки 
содержащей как целые, так и вещественные числа. 
Число считается целым, если у него нулевая дробная 
часть. Функция должна вернуть суммы всех целых и 
вещественных чисел в строке, а также их количества. 
Исходная строка передается в качестве параметра. 
Используя разработанную функцию обработать N строк, 
введенных пользователем.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <locale.h>

#define EPS 0.000001

void parsestr(char *str, int *nint, int *sumint, int *nfloat, double *sumfloat);
double mod(double val);

int main(void)
{
	setlocale(LC_ALL, "Ru");
	char str[50];// = "0,1 10,0 25 75,455 5,00000 60 25,4449";
	int nint = 0, nfloat = 0, sumint = 0, n = 0;
	double sumfloat = 0;

	printf("Введите количество строк: ");
	do
	{
		scanf("%d", &n);
		if(n > 0) break;
		printf("Некорректный ввод! Попробуйте снова: ");
	} while(1);

	fflush(stdin);
	for (int i = 0; i < n; i++)//ввод и парсинг
	{
		printf("Введите строку: ");
		gets(str);
		parsestr(str, &nint, &sumint, &nfloat, &sumfloat);
		printf("%14s\t%8s\t%14s\n", " ", "кол-во", "сумма");
		printf("%14s\t%8d\t%14d\n", "целых", nint, sumint);
		printf("%14s\t%8d\t%14lf\n\n", "вещественных", nfloat, sumfloat);
	}
	return 0;
}

void parsestr(char *str, int *nint, int *sumint, int *nfloat, double *sumfloat)
{
	double num;
	char *ptr = strtok(str, " ");
	while(ptr != NULL)
	{
		num = atof(ptr);
		if(mod(num) != 0) { *sumfloat += num; (*nfloat)++; }
		else { *sumint += num; (*nint)++; }
		ptr = strtok(NULL, " ");
	}
}
double mod(double val)
{
	val = trunc(val / EPS) * EPS;
	return val - floor(val);
}
