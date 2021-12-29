#include "../inc/philo.h"
#include <pthread.h>
#include <stdio.h>

t_needed *life_init(int argc, char *argv[], int philosopher)
{
	t_needed *sample;
	int i;

	i = 1;
	sample = malloc(sizeof(t_needed));
	while(--argc)
	{	
		sample->arguments[i - 1] = atoi(argv[i]); // careful !!! not my atoi
		i++;
	}
	sample->philosopher = philosopher;
	sample->arguments[i - 1] = -1;
	sample->sleeping = 0;
	sample->eating = 0;
	return (sample);
}

void *test(void *args)
{
	t_needed *life;


	life = args;
	if(!pthread_mutex_lock(&life->fork[0]))
	{printf("philosopher %d is picking" "\033[0;31m" " first fork" "\033[0m" ".\n", life->philosopher);
	pthread_mutex_lock(&life->fork[1]);
	printf("philosopher %d is picking" "\033[0;31m" " second fork" "\033[0m" ".\n", life->philosopher);
	printf("philosopher %d is" "\033[0;32m" " eating" "\033[0m" ".\n", life->philosopher);
	// while() count eating, make a funct?
	pthread_mutex_unlock(&life->fork[0]);
	pthread_mutex_unlock(&life->fork[1]);}
	// free args?
	free(args);
	return(NULL);
}

int main(int argc, char *argv[])
{
	int	*args;
	pthread_t id[6];
	int philo_count;
	int check_death = 1;
	t_needed *life; 

	args = parsed(argc, argv); // don't forget to free.
	while(check_death--)
	{	
		philo_count = 0;
		while(++philo_count < 6)
		{	
			life = life_init(argc, argv, philo_count);
			pthread_mutex_init(&life->fork[0], NULL);
			pthread_mutex_init(&life->fork[1], NULL);
			pthread_create(&id[philo_count - 1], NULL, &test, life);
		}

		philo_count = 0;
		while(++philo_count < 6)
			pthread_join(id[philo_count - 1], NULL);
	}
	return (0);
}