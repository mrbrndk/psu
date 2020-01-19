/*
Задан вещественный массив размера N.
Отсортировать по возрастанию элементы массива, 
расположенные на четных позициях, и по убыванию – на нечетных позициях. 
Пример: 2 7 4 5 1 0 9 6 8 3 > 1 7 2 6 4 5 8 3 9 0
*/

#include <stdio.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "Ru");
	unsigned n, number = 0;
	printf("Введите размер массива: ");
	do
	{
		scanf("%d", &n);
		scanf("%*[^\n]");
		if (n > 0) break;
		printf("Некорректный ввод! Попробуйте еще раз: ");
	} while (1);

	double a[n], minmax, flip;
	printf("Введите массив: ");
	for (unsigned i = 0; i < n; i++) scanf("%lf", &a[i]);

	for (unsigned i = 0; i < n; i++)
	{
		minmax = a[i];
		for (unsigned j = i; j < n; j += 2)
		{
			if ((i % 2 == 0 && a[j] < minmax) || (i % 2 != 0 && a[j] > minmax))
			{
				minmax = a[j];
				number = j;
			}

		}
		if(a[i] != minmax)
		{
			flip = a[i];
			a[i] = a[number];
			a[number] = flip;
		}
	}

	printf("Результат: ");
	for (unsigned i = 0; i < n; i++) printf("%lf%s", a[i], (i == n-1) ? "\n" : " ");
	return 0;
}
