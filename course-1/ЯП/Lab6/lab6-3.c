/*
Реализовать функцию, вычисляющую сумму вещественных чисел, 
переданных в качестве параметров, значение которых больше 
среднего значения всех параметров.
*/

#include <stdio.h>
#include <stdarg.h>
#include <locale.h>

double sum(int n, ...);

int main(void)
{
	setlocale(LC_ALL, "Ru");
	printf("Кол-во параметров = 3: %lf\n", sum(3, 45.8, 95.1, 69.5));
	printf("Кол-во параметров = 5: %lf\n", sum(5, 45.8, 95.1, 69.5, 1.72, 101.66)); 
	printf("Кол-во параметров = 8: %lf\n", sum(8, 45.8, 95.1, 69.5, 1.72, 101.66, 3.96, 65.11, 75.93)); 
	return 0;
}

double sum(int n, ...)
{
	double val = 0.0, cur = 0.0, result = 0.0;
	va_list ap;
	va_start(ap, n);

	for(int i = 0; i < n; i++) val += va_arg(ap, double);
	va_end(ap);
	val /= n; 

	va_start(ap, n);

	for(int i = 0; i < n; i++)
	{
		cur = va_arg(ap, double);
		if(cur > val) result += cur;
	}
	va_end(ap);
	return result;
}
