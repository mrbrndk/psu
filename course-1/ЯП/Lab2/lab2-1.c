/*
c =	e^|a*b|, 0.5 < a/b < 10
	sqrt(|a-b|), 0.1 < a/b < 0.5
	2*(a-b)^2, иначе
*/


#include <stdio.h>
#include <math.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "Ru");
	double a, b, c;
	printf("¬ведите a и b через пробел:\n");
	scanf("%lf %lf", &a, &b);
	if (0.5 < a / b && a / b < 10.0)//5 2 ~= 22003
	{
		printf("0.5 < a / b < 10\n");
		c = exp(fabs(a * b));
	}
	else if (0.1 < a / b && a / b < 0.5)//1 3 = 1.41
	{
		printf("0.1 < a / b < 0.5\n");
		c = sqrt(fabs(a - b));
	}
	else//30 3 = 1458
	{
		printf("иначе\n");
		c = 2 * pow(a - b, 2);
	}
	printf("–езультат: c = %lf\n", c);
	return 0;
}
