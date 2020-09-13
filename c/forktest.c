#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <inttypes.h>

int a = 42;
int b;

int main()
{
	printf("Main PID: %d\n", (int)getpid());

	b = 666;

	pid_t pid = fork();
	printf("fork() result: %d\n", pid);

	switch (pid)
	{
		case -1:
			printf("fork() Error\n");
			break;
		case 0:
			printf("In Child. Our PID: %d\n", (int)getpid());
			int suma = 0;
			for (int a = 0; a < 10000; a++)
			{
				suma += a;
			}

			printf("Child Sum: %d - a: %d - b: %d\n", suma, a, b);
			break;
		default:
			printf("In Parent. Our PID: %d\n", (int)getpid());
			int sumb = 0;
			for (int b = 0; b < 1000; b++)
			{
				sumb += b;
			}

			printf("Parent Sum: %d - a: %d - b: %d\n", sumb, a, b);

			printf("Waiting....\n");
			wait(NULL);
			printf("Done Waiting\n");
			break;
	}

	return 0;
}
