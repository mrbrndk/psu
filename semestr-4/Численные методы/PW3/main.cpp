#include <iostream>

#define N 3
double mx[N] = { -1.0, 0.0, 1.0 };
double my[N] = { 1.0, 0.0, 1.0 };
double x = -3.0;

int main()
{
	double p = 1.0, sum = 0.0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (j != i)
			{
				p *= (x - mx[j]) / (mx[i] - mx[j]);
			}
		}
		sum += my[i] * p;
		p = 1.0;
	}
	std::cout << "L(" << x << ") = " << sum << std::endl;
	getchar();
	return 0;
}