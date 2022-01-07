#include "../inc/philo.h"
#include <pthread.h>
#include <stdio.h>

t_needed *life_init(int philosopher, int *died)
{
	t_needed 	*sample;
	int 		i;

	i = 1;
	sample = malloc(sizeof(t_needed));
	// while(--argc)
	// {	
	// 	sample->arguments[i - 1] = atoi(argv[i]); // careful !!! not my atoi
	// 	i++;
	// }
	sample->died = died;
	sample->philosopher = philosopher;
	sample->arguments[i - 1] = -1;
	sample->sleeping = 0;
	sample->eating = 0;
	sample->death = 400;
	return (sample);
}

void *ded(void *args)
{
	t_needed *life;

	life = args;
	while(life->death)
	{	if(life->eating == 0)
			life->death--; 
		printf("I'm inside ded eating is %d\n", life->eating);
	}
	if(!life->death && *(life->died))
	{	
		*(life->died) = 0;
		printf("philosopher %d is " "\033[0;30m" "ded" "\033[0m" ".\n", life->philosopher);
	}
	return (NULL);
}

void *test(void *args)
{
	t_forks *life;
	int sleeping;
	int eating;
	pthread_mutex_t *fork[2];

	sleeping = 500;
	eating = 400;
	life = args;
	fork[0] = &life->fork;
	fork[1] = &life->next->fork;
	while(*(life->philosopher->died))
	{
		pthread_mutex_lock(fork[0]);
		pthread_mutex_lock(fork[1]);
		life->philosopher->death = 400;
		life->philosopher->eating = 1;
		if(*(life->philosopher->died))
		{printf("philosopher %d is picking" "\033[0;31m" " first fork" "\033[0m" ".\n", life->philosopher->philosopher);
		printf("philosopher %d is picking" "\033[0;31m" " second fork" "\033[0m" ".\n", life->philosopher->philosopher);
		printf("philosopher %d is" "\033[0;32m" " eating" "\033[0m" ".\n", life->philosopher->philosopher);
		while(eating--);}
		pthread_mutex_unlock(fork[0]);
		pthread_mutex_unlock(fork[1]);
		life->philosopher->eating = 0;
		if(*(life->philosopher->died))
		{printf("philosopher %d is " "\033[0;37m" "sleeping" "\033[0m" ".\n", life->philosopher->philosopher);
		while(sleeping--);}
		if(*(life->philosopher->died))
		printf("philosopher %d is " "\033[0;35m" "thinking" "\033[0m" ".\n", life->philosopher->philosopher);
	}
	return(NULL);
}

int main(int argc, char *argv[])
{
	// int	*args;
	(void) argc;
	(void) argv;
	pthread_t id[6];
	pthread_t idd[6];
	int philo_count;
	t_forks *forks;
	int died = 1;

	// args = parsed(argc, argv); // don't forget to free.
	forks = NULL;
	philo_count = 0;
	while(++philo_count < 6)
	{	
		new_philosopher(philo_count, &died, &forks);
		pthread_create(&id[philo_count - 1], NULL, &test, forks);
		pthread_create(&idd[philo_count - 1], NULL, &ded, forks->philosopher);
	}

	philo_count = 0;
	while(++philo_count < 6)
	{	
		pthread_join(id[philo_count - 1], NULL);
		pthread_join(idd[philo_count - 1], NULL);
	}
	return (0);
}