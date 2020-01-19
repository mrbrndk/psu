/*
Элементы равностороннего треугольника пронумерованы следующим образом: 
1 — сторона (a), 2 — радиус вписанной окружности (R1), 
3 — радиус описанной окружности (R2), 4 — площадь (S). 
Дан номер одного из этих элементов и его значение. 
Вывести значения остальных элементов данного треугольника (в том же порядке).
*/

#include <stdio.h>
#include <math.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "Ru");
	unsigned choice;
	double a, r1, r2, s, value;
	printf("1 - сторона (a)\n\
			\r2 - радиус вписанной окружности (R1)\n\
			\r3 - радиус описанной окружности (R2)\n\
			\r4 - площадь (S)\n\
			\rВыберите известный элемент: ");
	do
	{
		scanf("%d", &choice);
		if (choice > 0 && choice < 5) break;
		printf("Некорректный ввод! Попробуйте еще раз: ");
	} while (1);
	printf("Введите значение для выбранного элемента: ");
	do
	{
		scanf("%lf", &value);
		if (value > 0) break;
		printf("Некорректный ввод! Попробуйте еще раз: ");
	} while (1);
	switch (choice)
	{
		case 1: { a = value; break;	}
		case 2:	{ a = value * 2 * sqrt(3);	break; }
		case 3:	{ a = value * sqrt(3); break; }
		case 4: { a = sqrt(value / (sqrt(3) / 4.0)); break;	}
		default: return 0;
	}
	r1 = a / (2 * sqrt(3));
	r2 = a / sqrt(3);
	s = sqrt(3) / 4.0 * (a * a);
	printf("a = %lf\n", a);//2
	printf("R1 = %lf\n", r1);//0.577
	printf("R2 = %lf\n", r2);//1.15
	printf("S = %lf\n", s);//1.73
	return 0;
}
