/*
������ ��� ������������ ������� ������������� �������. 
��������� ������������ ���� ������, ���� ��� ��������. 
���������, �������� �� ���������� ������� ������������.
*/

#include <stdio.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "Ru");
	//row - ������, col - �������
	unsigned arow = 0, acol = 0,  brow = 0, bcol = 0, symmetry = 0; 
	printf("������� ���������� ����� � �������� � ������� �: ");
	do
	{
		scanf("%d %d", &arow, &acol);
		if (arow > 0 && acol > 0) break;
		printf("������������ ����! ���������� ��� ���: ");
	} while (1);
	printf("������� ���������� ����� � �������� � ������� B: ");
	do
	{
		scanf("%d %d", &brow, &bcol);
		if (brow > 0 && bcol > 0) break;
		printf("������������ ����! ���������� ��� ���: ");
	} while (1);
	if (acol != brow)
	{
		printf("��������� ����� ������ ����������!\n");
		return 0;
	}
	double a[arow][acol], b[brow][bcol], c[arow][bcol];
	printf("������� ������ A:\n");
	for (unsigned i = 0; i < arow; i++)
	{
		for (unsigned j = 0; j < acol; j++) scanf("%lf", &a[i][j]);
	}
	printf("������� ������ B:\n");
	for (unsigned i = 0; i < brow; i++)
	{
		for (unsigned j = 0; j < bcol; j++) scanf("%lf", &b[i][j]);
	}

	/*double a[2][3] = {{2, 1}, //3 x 2
					   {-3, 0}, 
					   {4, -1}};

	double b[3][2] = {{5, -1, 6}, //2 x 3
					  {-3, 0, 7}};

	double c[3][3] = {{1, 3, 0}, //3 x 3
					  {3, 2, 6},
					  {0, 6, 5}};*/
					
	for (unsigned i = 0; i < arow; i++)
	{
		for (unsigned j = 0; j < bcol; j++)
		{
			c[i][j] = 0;//�������������
			for (unsigned k = 0; k < acol; k++) c[i][j] += a[i][k] * b[k][j];
		}
	}
	printf("��������� �:\n");
	for (unsigned i = 0; i < arow; i++)
	{
		for (unsigned j = 0; j < bcol; j++) printf("%lf\t", c[i][j]);
		printf("\n");
	}

	if (arow == bcol)
	{
		symmetry = 1;
		for (unsigned i = 0; i < arow; i++)
		{
			for (unsigned j = i; j < arow; j++)
			{
				if (c[i][j] != c[j][i]) symmetry = 0;
			}
		}
	}
	if (symmetry == 1) printf("������� �������� ������������.\n");
	else printf("������� �� �������� ������������.\n");
	return 0;
}
