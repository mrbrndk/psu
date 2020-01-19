/*
�������� ��������������� ������������ ������������� ��������� �������: 
1 � ������� (a), 2 � ������ ��������� ���������� (R1), 
3 � ������ ��������� ���������� (R2), 4 � ������� (S). 
��� ����� ������ �� ���� ��������� � ��� ��������. 
������� �������� ��������� ��������� ������� ������������ (� ��� �� �������).
*/

#include <stdio.h>
#include <math.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "Ru");
	unsigned choice;
	double a, r1, r2, s, value;
	printf("1 - ������� (a)\n\
			\r2 - ������ ��������� ���������� (R1)\n\
			\r3 - ������ ��������� ���������� (R2)\n\
			\r4 - ������� (S)\n\
			\r�������� ��������� �������: ");
	do
	{
		scanf("%d", &choice);
		if (choice > 0 && choice < 5) break;
		printf("������������ ����! ���������� ��� ���: ");
	} while (1);
	printf("������� �������� ��� ���������� ��������: ");
	do
	{
		scanf("%lf", &value);
		if (value > 0) break;
		printf("������������ ����! ���������� ��� ���: ");
	} while (1);
	switch (choice)
	{
		case 1: { a = value; break;	}
		case 2:	{ a = value * 2 * sqrt(3);	break; }
		case 3:	{ a = value * sqrt(3); break; }
		case 4: { a = sqrt(value / (sqrt(3) / 4.0)); break;	}
		default: return 0;
	}
	r1 = a / (2 * sqrt(3));
	r2 = a / sqrt(3);
	s = sqrt(3) / 4.0 * (a * a);
	printf("a = %lf\n", a);//2
	printf("R1 = %lf\n", r1);//0.577
	printf("R2 = %lf\n", r2);//1.15
	printf("S = %lf\n", s);//1.73
	return 0;
}
