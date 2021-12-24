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
	pthread_mutex_lock(&life->fork[0]);
	printf("philosopher %d is picking" "\033[0;31m" " first fork" "\033[0m" ".\n", life->philosopher);
	pthread_mutex_lock(&life->fork[1]);
	printf("philosopher %d is picking" "\033[0;31m" " second fork" "\033[0m" ".\n", life->philosopher);
	printf("philosopher %d is" "\033[0;32m" " eating" "\033[0m" ".\n", life->philosopher);
	// while() count eating, make a funct?
	pthread_mutex_unlock(&life->fork[0]);
	pthread_mutex_unlock(&life->fork[1]);
	// free args?
	return(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t id[6];
	int philo_count;
	int check_death = 3;
	t_needed life = life_init(argc, argv);
	while(check_death--)
	{	
		philo_count = 0;
		while(++philo_count < 6)
		{	printf("supposed to be philo %d\n", philo_count);
			life.philosopher = philo_count;
			pthread_create(&id[philo_count - 1], NULL, &test, &life);
			// pthread_join(id[philo_count - 1], NULL);
		}

		philo_count = 0;
		while(++philo_count < 6)
			pthread_join(id[philo_count - 1], NULL);
	}
	return (0);
}