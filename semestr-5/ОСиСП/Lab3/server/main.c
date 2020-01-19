#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int sock;
	FILE *fout;
	char string1[50], string2[50], res = '0';
	int bytes_read;

	int listener = socket(AF_INET, SOCK_STREAM, 0);
	if(listener < 0)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(3425);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind");
		exit(2);
	}

	listen(listener, 1);

	while(1)
	{
		sock = accept(listener, NULL, NULL);
		if(sock < 0)
		{
			perror("accept");
			exit(3);
		}

		while(1)
		{
			bytes_read = recv(sock, string1, 50, 0);
			if(bytes_read <= 0) break;
			if((fout = fopen("/home/user/t3/input2.txt", "r")) != NULL)
			{
				while(!feof(fout))
				{
					if(fgets(string2, 50, fout) != NULL)
					{
						string2[strcspn(string2, "\r\n")] = 0;
						if(strcmp(string1, string2) == 0)
							res = '1';
					}
				}
				fclose(fout);
			}
			send(sock, &res, 1, 0);
			res = '0';
		}

		close(sock);
	}
	return 0;
}
