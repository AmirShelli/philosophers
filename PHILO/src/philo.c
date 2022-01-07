#include "../inc/philo.h"
#include <pthread.h>
#include <stdio.h>

t_needed *life_init(int argc, char *argv[], int philosopher, pthread_mutex_t *fork, int *died)
{
	t_needed *sample;
	int i;

	i = 1;
	sample = malloc(sizeof(t_needed));
	sample->fork = malloc(sizeof(pthread_mutex_t) * 2);
	while(--argc)
	{	
		sample->arguments[i - 1] = atoi(argv[i]); // careful !!! not my atoi
		i++;
	}
	sample->died = died;
	sample->philosopher = philosopher;
	sample->arguments[i - 1] = -1;
	sample->sleeping = 0;
	sample->eating = 0;
	sample->death = 400;
	sample->fork[0] = &fork[0];
	sample->fork[1] = &fork[1];
	return (sample);
}
void *ded(void *args)
{
	t_needed *life;

	life = args;
	while(--life->death); 
	if(!life->death && *(life->died))
	{	
		*(life->died) = 0;
		printf("philosopher %d is " "\033[0;30m" "ded" "\033[0m" ".\n", life->philosopher);
	}
	return (NULL);
}

void *test(void *args)
{
	t_needed *life;
	// int thinking;
	int sleeping;
	int eating;

	// thinking = 50000;
	sleeping = 500;
	eating = 400;
	life = args;
	while(*(life->died))
	{
		pthread_mutex_lock(life->fork[0]);
		life->death = 400;
		pthread_mutex_lock(life->fork[1]);
		if(*(life->died))
		{
		printf("philosopher %d is picking" "\033[0;31m" " first fork" "\033[0m" ".\n", life->philosopher);
		printf("philosopher %d is picking" "\033[0;31m" " second fork" "\033[0m" ".\n", life->philosopher);
		printf("philosopher %d is" "\033[0;32m" " eating" "\033[0m" ".\n", life->philosopher);
		while(eating--);}
		pthread_mutex_unlock(life->fork[0]);
		pthread_mutex_unlock(life->fork[1]);
		if(*(life->died))
		{printf("philosopher %d is " "\033[0;37m" "sleeping" "\033[0m" ".\n", life->philosopher);
		while(sleeping--);}
		if(*(life->died))
		printf("philosopher %d is " "\033[0;35m" "thinking" "\033[0m" ".\n", life->philosopher);
	}
	free(life);
	return(NULL);
}

int main(int argc, char *argv[])
{
	// int	*args;
	pthread_t id[6];
	pthread_t idd[6];
	int philo_count;
	t_needed *philosophers;
	pthread_mutex_t *fork;
	int died = 1;

	// args = parsed(argc, argv); // don't forget to free.
	philosophers = malloc(sizeof(t_needed));
	fork = malloc(sizeof(pthread_mutex_t) * 2);
	pthread_mutex_init(&fork[0], NULL);
	pthread_mutex_init(&fork[1], NULL);
	
	philo_count = 0;
	while(++philo_count < 6)
	{	
		philosophers = life_init(argc, argv, philo_count, fork, &died);
		pthread_create(&id[philo_count - 1], NULL, &test, philosophers);
		pthread_create(&idd[philo_count - 1], NULL, &ded, philosophers);
	}

	philo_count = 0;
	while(++philo_count < 6)
	{	
		pthread_join(id[philo_count - 1], NULL);
		pthread_join(idd[philo_count - 1], NULL);
	}
	return (0);
}