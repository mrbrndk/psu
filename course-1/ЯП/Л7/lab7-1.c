/*
� ������ ������� ���������� ����������� ��������� 
���������� ����� (��� ������) �������� ������� ��������. 
��� ����� ���������� � ���������� ��������� ������, 
� ���� ��� �� �������, �� �������� � ����������.

���� �������� �����, ����� ����� � ������������ �����.  
�������� ��� ����� � ���������� ������� � ���� words.txt, 
����� �����, ������������� �� �����������, � ���� integers.txt, 
������������ ����� � ������� �������� � ���� floats.txt.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <locale.h>

#define EPS 0.000001

double mod(double val);
int fcmp(const void *x1, const void *x2);
int icmp(const void *x1, const void *x2);
int scmp(const void *x1, const void *x2);

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Ru");
	FILE *file;
	int idata[50];
	double fdata[50];
	char sdata[50][50], input[50];
	unsigned fcount = 0, icount = 0, scount = 0;
	if(argc > 1 && (file = fopen(argv[1], "r")) != NULL)
	{
		printf("������ ���� ��������� � ���������� ��������� ������!\n");
	}
	else
	{
		printf("������� ��� ����� ��� ��������: ");
		do
		{
			gets(input);
			if((file = fopen(input, "r")) != NULL) break;
			printf("�� ������� ������� ��������� ����!\n");
		} while(1);
	}
	printf("������ ������\n");
	while(!feof(file))
	{
		if(fgets(input, 50, file) != NULL)
		{
			double num = atof(input);
			if(!num)
			{
				char *ptr = strtok(input, "\n");
				if(ptr != NULL) strcpy(sdata[scount], ptr);
				else strcpy(sdata[scount], input);
				scount++;
			}
			else if(!mod(num)) { idata[icount] = num; icount++; }
			else { fdata[fcount] = num; fcount++; }
		}
	}
	fclose(file);

	printf("��������� ������\n");
	qsort(fdata, fcount, sizeof(double), fcmp);
	qsort(idata, icount, sizeof(int), icmp);
	qsort(sdata, scount, sizeof(input), scmp);

	if((file = fopen("floats.txt", "w")) != NULL)
	{
		printf("������ floats.txt\n");
		for(unsigned i = 0; i < fcount; i++) fprintf(file, "%lf\n", fdata[i]);
		fclose(file);
	}
	if((file = fopen("integers.txt", "w")) != NULL)
	{
		printf("������ integers.txt\n");
		for(unsigned i = 0; i < icount; i++) fprintf(file, "%d\n", idata[i]);
		fclose(file);
	}
	if((file = fopen("words.txt", "w")) != NULL)
	{
		printf("������ words.txt\n");
		for(unsigned i = 0; i < scount; i++) fprintf(file, "%s\n", sdata[i]);
		fclose(file);
	}
	return 0;
}

double mod(double val)
{
	val = trunc(val / EPS) * EPS;
	return val - floor(val);
}
int fcmp(const void *x1, const void *x2)
{
	double result = ( *(double*)x2 - *(double*)x1 );
	if(fabs(result) < EPS) return 0;
	return (result > 0) ? 1 : -1;
}
int icmp(const void *x1, const void *x2) { return ( *(int*)x1 - *(int*)x2 ); }
int scmp(const void *x1, const void *x2) { return strcmp(x1, x2); }
