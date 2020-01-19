/*
������ ����������� ������� ������������������ � ������� main. 
��������� ����������� � ���������� ������: ������ ������ - ����� ������. 
����� ������� ������ ������ ����������� � ������������ ����� �, � 
������ �������������� ������, ������������ ���������� ���������. 

����� ������ ������ � ������, ���������� ������ 
���������� ��������. ������� ������ ������� ����������� ����������.
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
		printf("������� ������ ��� ������ ��� ������� ������ ��� ������:\n");
		gets(input);
		if(!strcmp(input, "")) break;
		char result = findchar(input, 0, strlen(input));
		if(!result) printf("�� �������!\n");
		else printf("������ ��������� ������: %c\n", result);
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

