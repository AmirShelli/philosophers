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
	t_hello *life;


	life = args;
	if(!pthread_mutex_lock(&life->fork[0]) && !pthread_mutex_lock(&life->fork[1]))
	{	
		printf("philosopher %d is picking" "\033[0;31m" " first fork" "\033[0m" ".\n", life->life->philosopher);
		printf("philosopher %d is picking" "\033[0;31m" " second fork" "\033[0m" ".\n", life->life->philosopher);
		printf("philosopher %d is" "\033[0;32m" " eating" "\033[0m" ".\n", life->life->philosopher);

	}
	else {puts("hey\n");}
	// while() count eating, make a funct?
	free(life->life);
	pthread_mutex_unlock(&life->fork[0]);
	pthread_mutex_unlock(&life->fork[1]);
	return(NULL);
}

int main(int argc, char *argv[])
{
	// int	*args;
	pthread_t id[6];
	int philo_count;
	int check_death = 1;
	t_hello *philosophers;

	// args = parsed(argc, argv); // don't forget to free.
	philosophers = malloc(sizeof(t_hello));
	pthread_mutex_init(&philosophers->fork[0], NULL);
	pthread_mutex_init(&philosophers->fork[1], NULL);
	while(check_death--)
	{	
		philo_count = 0;
		while(++philo_count < 6)
		{	
			philosophers->life = life_init(argc, argv, philo_count);
			printf("nya %d\n", philo_count);
			pthread_create(&id[philo_count - 1], NULL, &test, philosophers);
		}

		philo_count = 0;
		while(++philo_count < 6)
			pthread_join(id[philo_count - 1], NULL);
	}
	return (0);
}