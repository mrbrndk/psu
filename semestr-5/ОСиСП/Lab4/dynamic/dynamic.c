#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void search_words(char *file1, char* file2)
{
	FILE *fin, *fout;
	char string1[50], string2[50];
	if((fin = fopen(file1, "r")) != NULL)
	{
		while(!feof(fin))
		{
			if(fgets(string1, 50, fin) != NULL)
			{

				if((fout = fopen(file2, "r")) != NULL)
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
	return;
}
