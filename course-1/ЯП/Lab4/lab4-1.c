/*
Дана строка – предложение, содержащая целые числа. 
Упорядочить числа в строке по возрастанию. 
Вычислить сумму этих чисел.
*/

#include <stdio.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "Ru");
	char string[51];// = "12 7537   -456    3 10145 0001  -02";
	int numbers[51], num = 0, flip, sum = 0;
	unsigned find = 0, neg = 0;

	printf("Введите строку: ");
	gets(string);
	if(string[0] == 0)
	{
		printf("Строка не может быть пустой!\n");
		return 0;
	}
	for (unsigned i = 0; string[i] != 0; i++)//преобразование
	{
		if (string[i] == '-') neg = 1;
		else if (string[i] >= '0' && string[i] <= '9')
		{
			num *= 10;
			num += string[i] - '0';
		}
		else 
		{
			num = 0;
			neg = 0;
		}
		if (num > 0 && (string[i + 1] < '0' || string[i + 1] > '9'))
		{
			if (neg == 1) num *= -1;
			numbers[find] = num;
			sum += num;
			find++;
		}
	}
	for (unsigned i = 0; i < find; i++)//сортировка
	{
		num = i;
		for (unsigned j = i; j < find; j++) if (numbers[j] < numbers[num]) num = j;
		if (numbers[i] != numbers[num])
		{
			flip = numbers[i];
			numbers[i] = numbers[num];
			numbers[num] = flip;
		}
	}

	string[0] = 0;
	for (unsigned i = 0; i < find; i++) sprintf(string, "%s %d", string, numbers[i]);
	printf("Результат:");
	puts(string);
	printf("Сумма чисел: %d\n", sum);
	return 0;
}
