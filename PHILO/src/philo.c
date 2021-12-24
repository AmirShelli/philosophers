#include "../inc/philo.h"
#include <pthread.h>

t_needed life_init(int argc, char *argv[])
{
	t_needed sample;
	int i;

	i = 1;
	while(--argc)
	{	
		sample.arguments[i - 1] = atoi(argv[i]); // careful !!! not my atoi
		i++;
	}
	sample.arguments[i - 1] = -1;
	pthread_mutex_init(&sample.fork[0], NULL);
	pthread_mutex_init(&sample.fork[1], NULL);
	sample.sleeping = 0;
	sample.eating = 0;
	return (sample);
}

void *test(void *args)
{
	t_needed *life;

	life = args;
	printf("I'm inside the thread, sleeping is %d\n", life->sleeping);
	life->sleeping++;
	// free args?
	return(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t id[5];
	t_needed life = life_init(argc, argv);
	pthread_create(&id[0], NULL, &test, &life);
	pthread_join(id[0], NULL);
	printf("I'm outside the thread, sleeping is %d\n", life.sleeping);
	return (0);
}