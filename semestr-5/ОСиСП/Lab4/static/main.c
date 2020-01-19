#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void search_words(char* file1, char* file2);

int main(void)
{
	long time = clock();
	search_words("/home/user/t4/input.txt", "/home/user/t4/input2.txt");
	printf("Время выполнения: %ld мс\n", clock() - time);
	return 0;
}
