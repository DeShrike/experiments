#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <inttypes.h>

#define BUFFER_SIZE 1

int main()
{
	uint8_t buff[BUFFER_SIZE]; // needed for read and write functions

	// index [0] = read
	// index [1] = write
	int parentToChild[2];
	int childToParent[2];

	// Create pipe
	if (pipe(parentToChild) == -1)
	{
		printf("Pipe Error (A)\n");
		return 1;
	}

	// Create pipe
	if (pipe(childToParent) == -1)
	{
		printf("Pipe Error (B)\n");
		return 1;
	}

	printf("Main PID: %d\n", (int)getpid());

	switch (fork())
	{
		case -1:
			printf("fork() error\n");
			return -2;
		case 0:
			// In child process

			// close unneeded end of the pipes
			// close the write end
			if (close(parentToChild[1]) == -1)
			{
				printf("close error - parent to child write\n");
				return 3;
			}

			// close the read end
			if (close(childToParent[0]) == -1)
			{
				printf("close error - child to parent read\n");
				return 3;
			}

			printf("We are in child process. PID: %d\n", (int)getpid());

			for (int i = 0; i < 100; i++)
			{
				buff[0] = (uint8_t)i;
				if (write(childToParent[1], buff, sizeof(buff)) != sizeof(buff))
				{
					printf("Write error in child\n");
					return 4;
				}

				if (read(parentToChild[0], buff, sizeof(buff)) == -1)
				{
					printf("read error in child\n");
					return 4;
				}

				printf("In child recieving %d from parent. PID: %d\n", buff[0], (int)getpid());
			}

			if (close(childToParent[1]) == -1)
			{
				printf("close error - child to parent write\n");
				return 3;
			}

			break;
		default:
			// in parent process

			// close unneeded end of the pipes
			// close the write end
			if (close(childToParent[1]) == -1)
			{
				printf("close error - child to parent write\n");
				return 3;
			}

			// close the read end
			if (close(parentToChild[0]) == -1)
			{
				printf("close error - parent to child read\n");
				return 3;
			}

			printf("We are in parent process. PID: %d\n", (int)getpid());

			for (int i = 0; i < 100; i++)
			{
				buff[0] = (uint8_t)i;
				if (write(parentToChild[1], buff, sizeof(buff)) != sizeof(buff))
				{
					printf("Write error in parent\n");
					return 4;
				}

				if (read(childToParent[0], buff, sizeof(buff)) == -1)
				{
					printf("read error in parent\n");
					return 4;
				}

				printf("In parent recieving %d from child. PID: %d\n", buff[0], (int)getpid());
			}

			if (close(parentToChild[1]) == -1)
			{
				printf("close error - parent to child write\n");
				return 3;
			}

			wait(NULL);
			break;
	}

	return 0;
}
