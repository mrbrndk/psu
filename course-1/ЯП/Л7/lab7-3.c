/*
����������� ���������, ������� ��������� �� ��������� ���������� �����
������ ������������ ��������� � ������������ ������. ������ � ���������
����� �������� ��������� � ������ ������ � ����� ������. ���������
������������ �� � ���������� � �������������� �������� ����.
������������� ���������� ����������� ��������� ��������� ��������� �����.
��� ��������� ����� ���������� � ���������� ��������� ������, � ���
��������������� ����� ���������� �� ����� ��������� ����� ����� ������ 
���������� �� .bin. ���� � �������� ������ ���������� ������, �� ����������
�������� ��������� �� ������ � ��������� ������ ������ � ����� � ����������
���������. ���������� ������� ������� ����������� � 20 ������ ��������.

������������� (�� ������� ������������): ����������� ���� � ���������� � ���
�� �������, ���� ��� ����� �� ������� ��� ������� ������� (������ ����� ���).
��� ��������������� �����, � ���� ������, - result.bin. ����������
������������� ����������� 20 ������� ��������.

������������� �� ������ ���������� (�������� �������������). 
���������:
�	����� ���������� (����� ����������� �����) 
�	ID ��������� (����� ������������ ����� � 16-������ �������);
�	����� (������ 30 ��������);
�	���� � ����� ����������� (� ������� ��.��.���� ��:��).
������ �����: ����� ����������: ID ��������� ������ ���� � ����� �����������
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct
{
	int device;
	int id;
	char text[31];
	char date[17];
} Message;

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Ru");
	FILE *file;
	char input[50] = "input3.txt", line[70];
	int filter = 553;
	if(argc > 1 && (file = fopen(argv[1], "r")) != NULL)
	{
		printf("������ ���� %s, ��������� � ���������� ��������� ������.\n", argv[1]);
		char *ptr = strtok(argv[1], ".");
		if(ptr != NULL) strcpy(input, ptr);
		else strcpy(input, argv[1]);
		strcat(input, ".bin");
	}
	else
	{
		printf("������� ��� ����� ��� ��������: ");
		do
		{
			gets(input);
			if((file = fopen(input, "r")) != NULL) break;
			printf("�� ������� ������� ��������� ����! ���������� �����: ");
		} while(1);
		strcpy(input, "result.bin");
	}
	printf("������� ����� ����������: ");
	do
	{
		scanf("%d", &filter);
		if(filter >= 100 && filter <= 999) break;
		printf("������� �������� � ��������� 100-999! ����: ");
	} while(1);

	printf("������ ������\n");
	unsigned n = 0, count = 0, cur = 0, errline = 0;
	while(!feof(file) && !ferror(file)) if(fgets(line, sizeof(line), file) != NULL) n++;
	rewind(file);

	Message msg[n];
	while(!feof(file))
	{
		errline++;
		if(fgets(line, sizeof(line), file) != NULL && !ferror(file))
		{
			int ind = strcspn(line, "\n");
			line[ind] = 0;

			char parse[4][31];
			char *row = strtok(line, ": ");
			while(row != NULL && cur < 4)
			{
				strcpy(parse[cur], row);
				row = strtok(NULL, "\"");
				cur++;
			}
			if(cur < 4) printf("������ ��������� ������ %d!\n", errline);
			else if(atoi(parse[0]) == filter)
			{
				sscanf(parse[0], "%d", &msg[count].device);
				sscanf(parse[1], "%X", &msg[count].id);
				strcpy(msg[count].text, parse[2]);
				strcpy(msg[count].date, parse[3] + 1);//������� ���������� ������
				count++;
			}
			cur = 0;
		}
		else printf("������ ������ ����� � ������ %d!\n", errline);
	}
	fclose(file);

	for(unsigned i = 0; i < count; i++) printf("%d: %X \"%s\" %s\n", msg[i].device, msg[i].id, msg[i].text, msg[i].date);

	printf("������ ������... ");
	if((file = fopen(input, "wb")) != NULL)
	{
		fwrite(msg, sizeof(Message), count, file);
		if(!ferror(file)) printf("OK\n");
		fclose(file);
	}
	fflush(stdin);
	printf("��� ������ ��������� ����� ������� ��� ���.\n���� ������ ������ �������� ���������.\n");
	do
	{
		gets(input);
		if(!strlen(input)) return 0;
		else if((file = fopen(input, "rb")) != NULL) break;
		printf("�� ������� ������� ��������� ����! ���������� �����: ");
	} while(1);
	
	unsigned bn;
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);
	if(size % sizeof(Message))
	{
		fclose(file);
		printf("������ ������ ��������� �����!\n");
		return 0;
	}
	bn = size / sizeof(Message);
	Message check[bn];
	fread(check, sizeof(Message), bn, file);
	fclose(file);
	for(unsigned i = 0; i < bn; i++) printf("%d: %X \"%s\" %s\n", check[i].device, check[i].id, check[i].text, check[i].date);
	return 0;
}
