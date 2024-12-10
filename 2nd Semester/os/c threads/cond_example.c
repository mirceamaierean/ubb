#include "barrier.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// thread 1 generates numbers until it generates a multiple of "divisor" defined below
// thread 2 will print that number
// to actually see the conditional variable doing work, we have to start thread 2 before thread 1
// otherwise thread 1 will lock the mutex before thread 2 will have a chance to even start
// alternatively, we could use a barrier to ensure that both threads are created before either of them attempts to do work

typedef struct
{
	int *num, *divisor;
	pthread_mutex_t *mtx;
	pthread_cond_t *cond;
} data;

void *f(void *a)
{
	data arg = *((data *)a);
	printf("Thread 1 starting...\n");
	pthread_mutex_lock(arg.mtx);
	printf("Thread 1 has locked mutex\n");
	while (*(arg.num) == 0 || *(arg.num) % *(arg.divisor) != 0)
	{
		*(arg.num) = random() % 1000 + 1;
		printf("Thread 1 has generated %d\n", *(arg.num));
	}
	printf("Thread 1 has sent signal\n");
	pthread_cond_signal(arg.cond);
	printf("Thread 1 unlocking the mutex\n");
	pthread_mutex_unlock(arg.mtx);
	return NULL;
}

void *g(void *a)
{
	data arg = *((data *)a);
	printf("Thread 2 starting...\n");
	pthread_mutex_lock(arg.mtx);
	printf("Thread 2 has locked the mutex\n");

	printf("Thread 2 is waiting for a signal\n");
	pthread_cond_wait(arg.cond, arg.mtx);

	printf("Thread 2 has been signaled to print %d\n", *(arg.num));
	pthread_mutex_unlock(arg.mtx);
	return NULL;
}

int main(int argc, char *argv[])
{
	srandom(getpid());

	// Create mutex
	pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx, NULL);

	// Create Conditional
	pthread_cond_t *cond = malloc(sizeof(pthread_cond_t));
	pthread_cond_init(cond, NULL);

	// Create Darta
	data *args = malloc(sizeof(data) * 2);
	int *num = malloc(sizeof(int)), *divisor = malloc(sizeof(int));
	*num = 0;
	*divisor = 5;

	if (argc > 1)
		*divisor = atoi(argv[1]);

	printf("Divisor is %d\n", *divisor);

	for (int i = 0; i <= 1; ++i)
	{
		args[i].num = num;
		args[i].divisor = divisor;
		args[i].mtx = mtx;
		args[i].cond = cond;
	}

	// Create threads
	pthread_t th1, th2;

	if (pthread_create(&th2, NULL, g, &args[1]))
	{
		perror("error creating thread 2");
		exit(1);
	}

	if (pthread_create(&th1, NULL, f, &args[0]))
	{
		perror("error creating thread 1");
		exit(1);
	}

	pthread_join(th2, NULL);
	pthread_join(th1, NULL);

	// Destroy everything
	pthread_mutex_destroy(mtx);
	pthread_cond_destroy(cond);

	free(divisor);
	free(num);
	free(args);
	free(mtx);
	free(cond);

	return 0;
}
