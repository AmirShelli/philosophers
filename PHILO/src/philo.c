#include "../inc/philo.h"
#include <pthread.h>
#include <stdio.h>

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
	if(pthread_mutex_lock(&life->fork[0]) != 0) //put in a func or smth
		puts("can't lock!!!");
	printf("philosopher %d is picking first fork.\n", life->philosopher);
	if(pthread_mutex_lock(&life->fork[1]) != 0)
		puts("can't lock!!!");
	printf("philosopher %d is picking second fork.\n", life->philosopher);
	printf("philosopher %d is eating.\n", life->philosopher);
	pthread_mutex_unlock(&life->fork[0]);
	pthread_mutex_unlock(&life->fork[1]);

	// free args?
	return(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t id[5];
	int philo_count;
	int check_death = 3;
	t_needed life = life_init(argc, argv);
	while(check_death--) //checks deaths
	{	
		philo_count = 1;
		while(philo_count++ < 5)
			pthread_create(&id[philo_count], NULL, &test, &life);
		philo_count = 1;
		while(philo_count++ < 5)
			pthread_join(id[philo_count], NULL);
	}
	
	pthread_join(id[0], NULL);
	printf("I'm outside the thread, sleeping is %d\n", life.sleeping);
	return (0);
}