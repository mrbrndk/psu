/*
Работу рекурсивной функции продемонстрировать в функции main. 
Программу реализовать в диалоговом режиме: запрос данных - вывод ответа. 
После каждого вывода ответа запрашивать у пользователя выход и, в 
случае положительного ответа, осуществлять завершение программы. 

Найти первый символ в строке, являющийся буквой 
латинского алфавита. Функцию поиска символа реализовать рекурсивно.
*/

#include <stdio.h>
#include <string.h>
#include <locale.h>

char findchar(char *arr, unsigned start, unsigned end);

int main(void)
{
	setlocale(LC_ALL, "Ru");
	char input[80];
	do
	{
		printf("Введите строку для поиска или введите пустую для выхода:\n");
		gets(input);
		if(!strcmp(input, "")) break;
		char result = findchar(input, 0, strlen(input));
		if(!result) printf("Не найдено!\n");
		else printf("Первый латинский символ: %c\n", result);
	} while(1);
	return 0;
}

char findchar(char *arr, unsigned start, unsigned end)
{
	if(start < end)
	{
		if((arr[start] >= 'A' && arr[start] <= 'Z') || 
			(arr[start] >= 'a' && arr[start] <= 'z')) return arr[start];
		return findchar(arr, start + 1, end);
	}
	else return 0;
}

