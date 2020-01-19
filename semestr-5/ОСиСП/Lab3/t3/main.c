#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>

int main(void)
{
	long time = clock();
	FILE *fin;
	char string[50], res = '0';

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(3425); // или любой другой порт...
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("connect");
		exit(2);
	}

	if((fin = fopen("/home/user/t3/input.txt", "r")) != NULL)
	{
		while(!feof(fin))
		{
			if(fgets(string, 50, fin) != NULL)
			{
				string[strcspn(string, "\r\n")] = 0;
				send(sock, string, 50, 0);
				recv(sock, &res, 1, 0);
				if(res == '1') printf("%s;\n", string);
				res = '0';
			}
		}
		fclose(fin);
	}
	close(sock);
	printf("Время выполнения: %ld мс\n", clock() - time);
	return 0;
}
