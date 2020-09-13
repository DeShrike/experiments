#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>  // needed for getpid()
#include <unistd.h>     // needed for getpid()

void *aThread();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

int main()
{
	int rc1, rc2, rc3;
	pthread_t thread1, thread2, thread3;

	if ((rc1 = pthread_create( &thread1, NULL, &aThread, NULL)))
	{
		printf("Thread creation failed: %d\n", rc1);
		return 1;
	}

	if ((rc2 = pthread_create( &thread2, NULL, &aThread, NULL)))
	{
		printf("Thread creation failed: %d\n", rc2);
		return 1;
	}

	if ((rc3 = pthread_create( &thread3, NULL, &aThread, NULL)))
	{
		printf("Thread creation failed: %d\n", rc3);
		return 1;
	}

	printf("Main Process PID: %d\n", (int)getpid());

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	printf("Main Process PID: %d\n", (int)getpid());

	exit(EXIT_SUCCESS);
	return 0;
}

void* aThread()
{
	for (int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex1);
		counter++;
		pthread_mutex_unlock(&mutex1);
	}

	pthread_mutex_lock(&mutex1);
	printf("Counter value: %d from PID: %d\n", counter, (int)getpid());
	pthread_mutex_unlock(&mutex1);
}
