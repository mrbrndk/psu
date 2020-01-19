#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_THREADS 128

pthread_t thrs[MAX_THREADS];
pthread_mutex_t mutex;
int pcounter = 0;

void* thread(void *args)
{

    FILE *fout;
    char *string1 = (char *) args;
    char string2[50];
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

    return 0;
}

int main(void)
{
    long time =  clock();
    FILE *fin;
    char string1[MAX_THREADS][50];

	if((fin = fopen("/home/user/t2/input.txt", "r")) != NULL)
    {
        while(!feof(fin))
        {
            if(fgets(string1[pcounter], 50, fin) != NULL)
            {
                if(!pthread_create(&thrs[pcounter], NULL, thread, string1[pcounter])) pcounter++;
                else
                {
                    perror("Cannot create a thread");
                    abort();
                }

            }
        }
        for(int i = 0; i < pcounter; i++)
        {
            if(pthread_join(thrs[i], NULL))//при значении отличном от нуля
            {
                perror("Cannot join a thread");
                abort();
            }
        }
        fclose(fin);
    }
    printf("Время выполнения: %ld мс\n", clock() - time);
    printf("Потоков было задействовано: %d\n", pcounter);
    return 0;
}

