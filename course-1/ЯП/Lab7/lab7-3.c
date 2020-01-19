/*
Реализовать программу, которая считывает из исходного текстового файла
записи определенной структуры в динамический массив. Записи в текстовом
файле хранятся построчно – каждая запись в одной строке. Программа
обрабатывает их и записывает в результирующий бинарный файл.
Дополнительно необходимо разработать программу просмотра бинарного файла.
Имя исходного файла передается в параметрах командной строки, а имя
результирующего файла образуется из имени исходного файла путем замены 
расширения на .bin. Если в исходных данных содержится ошибка, то необходимо
выводить сообщение об ошибке с указанием номера строки в файле и продолжать
обработку. Выполнение данного задания оценивается в 20 баллов рейтинга.

ДОПОЛНИТЕЛЬНО (по желанию разработчика): Реализовать ввод с клавиатуры в том
же формате, если имя файла не указано или указано неверно (такого файла нет).
Имя результирующего файла, в этом случае, - result.bin. Выполнение
дополнительно оценивается 20 баллами рейтинга.

Отфильтровать по номеру устройства (вводится пользователем). 
СООБЩЕНИЕ:
•	номер устройства (целое трехзначное число) 
•	ID сообщения (целое восьмизначно число в 16-ричной системе);
•	текст (строка 30 символов);
•	дата и время отправления (в формате дд.мм.гггг чч:мм).
Формат ввода: Номер устройства: ID сообщения «Текст» Дата и время отправления
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
		printf("Открыт файл %s, указанный в параметрах командной строки.\n", argv[1]);
		char *ptr = strtok(argv[1], ".");
		if(ptr != NULL) strcpy(input, ptr);
		else strcpy(input, argv[1]);
		strcat(input, ".bin");
	}
	else
	{
		printf("Введите имя файла для открытия: ");
		do
		{
			gets(input);
			if((file = fopen(input, "r")) != NULL) break;
			printf("Не удалось открыть указанный файл! Попробуйте снова: ");
		} while(1);
		strcpy(input, "result.bin");
	}
	printf("Введите номер устройства: ");
	do
	{
		scanf("%d", &filter);
		if(filter >= 100 && filter <= 999) break;
		printf("Укажите значение в диапазоне 100-999! Ввод: ");
	} while(1);

	printf("Чтение данных\n");
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
			if(cur < 4) printf("Ошибка обработки строки %d!\n", errline);
			else if(atoi(parse[0]) == filter)
			{
				sscanf(parse[0], "%d", &msg[count].device);
				sscanf(parse[1], "%X", &msg[count].id);
				strcpy(msg[count].text, parse[2]);
				strcpy(msg[count].date, parse[3] + 1);//удаляем оставшийся пробел
				count++;
			}
			cur = 0;
		}
		else printf("Ошибка чтения файла в строке %d!\n", errline);
	}
	fclose(file);

	for(unsigned i = 0; i < count; i++) printf("%d: %X \"%s\" %s\n", msg[i].device, msg[i].id, msg[i].text, msg[i].date);

	printf("Запись данных... ");
	if((file = fopen(input, "wb")) != NULL)
	{
		fwrite(msg, sizeof(Message), count, file);
		if(!ferror(file)) printf("OK\n");
		fclose(file);
	}
	fflush(stdin);
	printf("Для чтения бинарного файла введите его имя.\nВвод пустой строки завершит программу.\n");
	do
	{
		gets(input);
		if(!strlen(input)) return 0;
		else if((file = fopen(input, "rb")) != NULL) break;
		printf("Не удалось открыть указанный файл! Попробуйте снова: ");
	} while(1);
	
	unsigned bn;
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);
	if(size % sizeof(Message))
	{
		fclose(file);
		printf("Ошибка чтения бинарного файла!\n");
		return 0;
	}
	bn = size / sizeof(Message);
	Message check[bn];
	fread(check, sizeof(Message), bn, file);
	fclose(file);
	for(unsigned i = 0; i < bn; i++) printf("%d: %X \"%s\" %s\n", check[i].device, check[i].id, check[i].text, check[i].date);
	return 0;
}
