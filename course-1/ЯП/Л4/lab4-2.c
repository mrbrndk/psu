/*
����������� ��������� �������� �������� �������.
������������ ����� ����� �� ����� 80 ��������. 
��� ���������� ��������� ���������� ������������ 
������� ��� ��������� ����� �� ��������� stdlib.h � string.h 

��� ������ ���������� (����������� 30 ����������). 
������ �������� �������� �������: 
���=��������, ��� ��� � ������, �������� � ������������ �����. 
���� �������� ��������� ���������� ���������� (�� �����), 
�� ����������� ������� �� ��������. ������� ������, 
���������� �� ���������� ��������� ���������� (� ������� ��������). 
���� ������ ���������� ������������ ���� �� ����� ������ ������, 
���� �� ���������� ������������� �������.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "Ru");
	/*char input[12][12] = {
						"7=2,06",
						"3=1,25",
						"5=1,76",
						"4=9,52",
						"7=1,65",
						"1=5,01",
						"3=4,89",
						"5=1,05",
						"2=2,38",
						"2=7,55",
						"4=3,57",
						"8=9,04"};*/

	char put[81], keys[31][81], key[81];
	double values[31], val = 0.0;
	unsigned counts[31], count = 0, find = 0, max = 0;
	
	printf("������� ������ ������� '����=��������':\n");
	for (unsigned i = 0; i < 31; i++)//���� � ������
	{
		do
		{
			gets(put);
			if(!strcmp(put, "")) break;
			char *ptr = strtok(put, "=");
			if(ptr != NULL)
			{
				strcpy(key, ptr);
				ptr = strtok(NULL, "=");
				if(ptr != NULL) 
				{
					val = atof(ptr);
					break;
				}
			}
			printf("������������ ����! ���������� ��� ���:\n");
		} while (1);
		if(!strcmp(put, "")) break;
		
		for (unsigned j = 0; j < count; j++)
		{	
			if (!strcmp(keys[j], key))
			{
				values[j] += val;
				counts[j]++;
				find = 1;
				break;
			}
		}
		if (!find) 
		{
			strcpy(keys[count], key);
			values[count] = val;
			counts[count] = 1;
			count++;
		}
		find = 0;
	}
	for (unsigned i = 0; i < count; i++) values[i] = values[i] / counts[i];//���������� ��������
	printf("���������:\n");
	for (unsigned i = 0; i < count; i++)//����������
	{
		max = i;
		for (unsigned j = i; j < count; j++) if (values[j] > values[max]) max = j;
		if (values[i] != values[max])
		{
			val = values[i];
			values[i] = values[max];
			values[max] = val;
			strcpy(key, keys[i]);
			strcpy(keys[i], keys[max]);
			strcpy(keys[max], key);
		}
		sprintf(put, "%s=%lf", keys[i], values[i]);
		puts(put);
	}
	return 0;
}
