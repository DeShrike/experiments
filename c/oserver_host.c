#include "oserver.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <inttypes.h>

int main()
{
	int fd, sockfd;

	printf("Setup\n");

	sockfd = oserver_setup();

	printf("Accepting...\n");

	fd = accept(sockfd, NULL, NULL);
	if (fd < 0)
	{
		err(1, "Accepting connection on TCP socket");
		return 1;
	}

	printf("Client connected\n");

	if (fork() == 0)
	{
		printf("Serving...\n");
		oserver_serve(fd);
		exit(0);
		return 0;
	}
	else
	{
		close(fd);
	}

	printf("Waiting...\n");
	wait(NULL);
	printf("Done Waiting\n");
}
