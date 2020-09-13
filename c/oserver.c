#include "oserver.h"
//#include <ccan/read_write_all/read_write_all.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void oserver_serve(int fd)
{
	char buf[1024];
	unsigned int i;

	printf("Serve: Reading from socket...\n");

	for (i = 0; i < sizeof(buf) - 1; i++)
	{
		if (read(fd, &buf[i], 1) != 1)
		{
			errx(1, "Client Disconnected");
		}

		if (buf[i] == '\n' || buf[i] == '\r')
		{
			break;
		}

		buf[i] = toupper(buf[i]);
	}

	buf[i] = '\0';

	printf("Serve: Sending...\n");

	char *prompt1 = "Louder: '";
	char *prompt2 = "'\r\n";

	if (!write(fd, prompt1, strlen(prompt1)) ||
		!write(fd, buf, i) ||
		!write(fd, prompt2, strlen(prompt2))
		)
	{
		err(1, "Write Failed");
	}

	sleep(1);

	exit(0);
}

int oserver_setup(void)
{
	int sockfd;
	int one = 1;

	union {
		struct sockaddr addr;
		struct sockaddr_in in;
	} u;

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0)
	{
		err(1, "Creating TCP socket");
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)))
	{
		warn("Setting socket reuse");
	}

	u.in.sin_family = AF_INET;
	u.in.sin_port = htons(OSERVER_PORT);
	u.in.sin_addr.s_addr = INADDR_ANY;
	if (bind(sockfd, &u.addr, sizeof(u.in)) == -1)
	{
		err(1, "Binding CTP socket");
	}

	if (listen(sockfd, 0) != 0)
	{
		err(1, "Listening on TCP socket");
	}

	printf("Server ready. Use telnet to connect to port %d\n", OSERVER_PORT);
	printf("Type some text and press enter.\n");

	return sockfd;
}
