/*
� ������ ������� ���������� ����������� ��������� ��������� 
����� (��� ������) �������� ������� ��������. ��� ����� 
���������� � ���������� ��������� ������, � ���� ��� ��� �� 
�������, �� �������� � ����������. ��� ���������� ������� 
����������� ��������� ��������� ��������� �����.

��� ����, ���������� ���������� (���������� ������ � 
������ � ������������ ����� ���� double). ������� �� 
����� ��� ���������� ������������ ��� � ��� ��� �. 
���������� ���������� ����������� �� ���������, � 
������� ��� �����������, � ������ ��������� � �� �� �����.
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
	printf("������������� input.bin? (0 - ���, 1 - ��)\n");
	do
	{
		scanf("%d", &needgen);
		if(needgen >= 0 && needgen <= 1) break;
		printf("������ 0 - ���, 1 - ��! �����: ");
	} while(1);
	if((needgen && (file = fopen("input.bin", "wb")) != NULL))//���������
	{
		Coord gen[5] = {	{1.0, 	1.0, 	3.0,	0},
							{3.0, 	-3.0, 	2.0,	0},
							{-3.0, 	-3.0, 	2.0,	0},
							{-3.0, 	3.0, 	2.0,	0},
							{3.0, 	3.0, 	2.0,	0}};
		
		fwrite(gen, sizeof(Coord), 5, file);
		fclose(file);
		printf("C����������� input.bin!\n");
	}

	char input[50];
	fflush(stdin);
	if(argc > 1 && (file = fopen(argv[1], "rb")) != NULL)
	{
		printf("������ ���� ��������� � ���������� ��������� ������.\n");
	}
	else
	{
		printf("������� ��� ����� ��� ��������: ");
		do
		{
			gets(input);
			if((file = fopen(input, "rb")) != NULL) break;
			printf("�� ������� ������� ��������� ����!\n");
		} while(1);
	}

	printf("������ ������\n");
	unsigned n, count = 0;
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);
	if(size % sizeof(Coord))
	{
		fclose(file);
		printf("������ ������ �����!\n");
		return 0;
	}
	n = size / sizeof(Coord);
	Coord coord[n];
	fread(coord, sizeof(Coord), n, file);
	fclose(file);
	for(unsigned i = 0; i < n; i++) printf("%lf %lf %lf %u\n", coord[i].x, coord[i].y, coord[i].r, coord[i].q);
	
	printf("\n��������� ������\n");
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
		printf("\n������ ������\n");
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
