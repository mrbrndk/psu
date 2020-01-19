/*
В данном задании необходимо осуществить обработку бинарного 
файла (или файлов) согласно условию варианта. Имя файла 
передается в параметрах командной строки, а если оно там не 
указано, то вводится с клавиатуры. При выполнении заданий 
реализовать программу генерации исходного файла.

Дан файл, содержащий окружности (координаты центра и 
радиус – вещественные числа типа double). Удалить из 
файла все окружности пересекающие ось Х или ось У. 
Оставшиеся окружности упорядочить по четвертям, в 
которых они расположены, а внутри четвертей – по их длине.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#define EPS 0.000001

typedef struct
{
	double x;
	double y;
	double r;
	unsigned q;
} Coord;

int cmp(const void *a, const void *b);

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Ru");
	FILE *file;
	int needgen;
	printf("Сгенерировать input.bin? (0 - нет, 1 - да)\n");
	do
	{
		scanf("%d", &needgen);
		if(needgen >= 0 && needgen <= 1) break;
		printf("Только 0 - нет, 1 - да! Ответ: ");
	} while(1);
	if((needgen && (file = fopen("input.bin", "wb")) != NULL))//генерация
	{
		Coord gen[5] = {	{1.0, 	1.0, 	3.0,	0},
							{3.0, 	-3.0, 	2.0,	0},
							{-3.0, 	-3.0, 	2.0,	0},
							{-3.0, 	3.0, 	2.0,	0},
							{3.0, 	3.0, 	2.0,	0}};
		
		fwrite(gen, sizeof(Coord), 5, file);
		fclose(file);
		printf("Cгенерирован input.bin!\n");
	}

	char input[50];
	fflush(stdin);
	if(argc > 1 && (file = fopen(argv[1], "rb")) != NULL)
	{
		printf("Открыт файл указанный в параметрах командной строки.\n");
	}
	else
	{
		printf("Введите имя файла для открытия: ");
		do
		{
			gets(input);
			if((file = fopen(input, "rb")) != NULL) break;
			printf("Не удалось открыть указанный файл!\n");
		} while(1);
	}

	printf("Чтение данных\n");
	unsigned n, count = 0;
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);
	if(size % sizeof(Coord))
	{
		fclose(file);
		printf("Ошибка чтения файла!\n");
		return 0;
	}
	n = size / sizeof(Coord);
	Coord coord[n];
	fread(coord, sizeof(Coord), n, file);
	fclose(file);
	for(unsigned i = 0; i < n; i++) printf("%lf %lf %lf %u\n", coord[i].x, coord[i].y, coord[i].r, coord[i].q);
	
	printf("\nОбработка данных\n");
	for(unsigned i = 0; i < n; i++)
	{
		if(fabs(coord[i].x) - coord[i].r > EPS && fabs(coord[i].y) - coord[i].r > EPS)
		{
			if(coord[i].y > 0) coord[i].q = (coord[i].x > 0) ? 1 : 2;
			else coord[i].q = (coord[i].x < 0) ? 3 : 4;
			coord[count] = coord[i];
			count++;
		}
	}
	n = count;
	qsort(coord, n, sizeof(Coord), cmp);
	for(unsigned i = 0; i < n; i++) if(coord[i].q > 0) printf("%lf %lf %lf %u\n", coord[i].x, coord[i].y, coord[i].r, coord[i].q);
	if((file = fopen(input, "wb")) != NULL)
	{
		printf("\nЗапись данных\n");
		fwrite(coord, sizeof(Coord), n, file);
		fclose(file);
	}
	return 0;
}

int cmp(const void *val1, const void *val2)
{
	const Coord *a = (const Coord *)val1;
	const Coord *b = (const Coord *)val2;
	return ((a->q) - (b->q));
}
