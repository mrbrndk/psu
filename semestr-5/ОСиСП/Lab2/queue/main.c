#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
	long time = clock();
	FILE *fin, *fout;
	char string1[50], string2[50];
	if((fin = fopen("/home/user/t2/input.txt", "r")) != NULL)
	{
		while(!feof(fin))
		{
			if(fgets(string1, 50, fin) != NULL)
			{

				if((fout = fopen("/home/user/t2/input2.txt", "r")) != NULL)
				{
					while(!feof(fout))
					{
						if(fgets(string2, 50, fout) != NULL)
						{
							string1[strcspn(string1, "\r\n")] = 0;
							string2[strcspn(string2, "\r\n")] = 0;
							if(strcmp(string1, string2) == 0)
								printf("%s;\n", string1);
						}
					}
					fclose(fout);
				}

			}
		}
		fclose(fin);
	}
	printf("Время выполнения: %ld мс\n", clock() - time);
	return 0;
}

