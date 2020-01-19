/*
Определить количество n-значных положительных целых чисел, 
среднее арифметическое цифр которого равняется числу K 
с точностью eps. Число n вводится пользователем (n <= 10). 
Числа К и eps вещественные и вводятся пользователем.
*/

#include <stdio.h>
#include <math.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "Ru");
	unsigned n, start = 1, result = 0;
	double k, eps;
	printf("Введите n-значность чисел: ");
	do
	{
		scanf("%d", &n);
		if (n > 0 && n <= 10) break;
		printf("Некорректный ввод! Попробуйте еще раз: ");
	} while (1);

	printf("Введите среднее арифметическое цифр K: ");
	do
	{
		scanf("%lf", &k);
		if (k > 0.0) break;
		printf("Некорректный ввод! Попробуйте еще раз: ");
	} while (1);

	printf("Введите точность eps: ");
	do
	{
		scanf("%lf", &eps);
		if (eps > 0.0) break;
		printf("Некорректный ввод! Попробуйте еще раз: ");
	} while (1);
	
	for (unsigned i = 0; i < n - 1; i++) start *= 10;
	for (unsigned i = start; i < start * 10; i++)
	{
		double f, sum = 0;
		for (unsigned j = i; j > 0; j /= 10) sum += j % 10;
		f = trunc(sum / n / eps) * eps;
		if (f == k)	result++;
	}
	printf("Количество: %d\n", result);
	return 0;
}
