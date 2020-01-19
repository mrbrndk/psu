/*
����� ������������� ������ �������� N. 
�������� ������� ����� � ����������� � ������������ ������. 
���� ����� ����� ���������, �� ������ ��������� �� ���.
*/

#include <stdio.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "Ru");
	unsigned n = 0, minsize = 0, maxsize = 0, minpos = 0, maxpos = 0, count = 0;
	printf("������� ������ �������: ");
	do
	{
		scanf("%d", &n);
		scanf("%*[^\n]");
		if (n > 0) break;
		printf("������������ ����! ���������� ��� ���: ");
	} while (1);

	int a[n], find = 0, flip;
	printf("������� ������:\t");
	for (unsigned i = 0; i < n; i++) scanf("%d", &a[i]);

	//int a[] = {2, 2, 0, 0, 7, 7, 7, 9, 9, 9};
	//int a[] = {2, 2, 2, 0, 0, 0, 7, 7, 9, 9};
	//int a[] = {2, 0, 3, 3, 7, 7, 7, 9, 9, 9};
	//int a[] = {2, 2, 2, 0, 0, 0, 7, 7, 3, 9};

	for (unsigned i = 0; i < n + 1; i++)
	{
		if (find != a[i] && count > 0)//����� �����
		{
			if (count <= minsize || minsize == 0)
			{
				minsize = count;
				minpos = i - count;
			}
			if (count >= maxsize || maxsize == 0)
			{
				maxsize = count;
				maxpos = i - count;
			}
			count = 0;
		}
		if (i < n)
		{
			count++;
			find = a[i];
		}
	}

	if(minpos < maxpos)//�������� ���������� �����
	{
		flip = a[minpos];
		a[minpos] = a[maxpos + maxsize - 1];
		a[maxpos + maxsize - 1] = flip;
		for (unsigned i = maxpos - 1; i > minpos + minsize - 1; i--) a[maxsize - minsize + i] = a[i];//�������� �������� ����� �������
		for (unsigned i = minpos; i < minpos + maxsize; i++) a[i] = a[minpos];//��������� �����
		for (unsigned i = maxsize - minsize + maxpos; i < maxpos + maxsize; i++) a[i] = a[maxpos + maxsize - 1];//��������� �����
	}
	else 
	{
		flip = a[maxpos];
		a[maxpos] = a[minpos + minsize - 1];
		a[minpos + minsize - 1] = flip;
		for (unsigned i = maxpos + maxsize; i < minpos; i++) a[minsize - maxsize + i] = a[i];
		for (unsigned i = maxpos; i < maxpos + minsize; i++) a[i] = a[maxpos];
		for (unsigned i = minsize - maxsize + minpos; i < minpos + minsize; i++) a[i] = a[minpos + minsize - 1];
	}
	
	printf("���������:\t");
	for (unsigned i = 0; i < n; i++) printf("%d%s", a[i], (i == n-1) ? "\n" : " ");
	return 0;
}
