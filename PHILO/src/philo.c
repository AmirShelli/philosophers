#include "../inc/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

long int since_last_meal(t_needed *life)
{
	struct timeval current_time;
	long int current;
	long int meal_time;

	gettimeofday(&current_time, NULL);
	meal_time = (life->last_meal.tv_sec) * 1000 + (life->last_meal.tv_usec) / 1000;
	current = (current_time.tv_sec) * 1000 + (current_time.tv_usec) / 1000;
	return (current - meal_time);
}

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
	pthread_mutex_init(&sample->is_eating, NULL);
	sample->died = died;
	sample->philosopher = philosopher;
	sample->arguments[i - 1] = -1;
	sample->sleeping = 0;
	sample->eating = 0;
	sample->death = 40000000;
	return (sample);
}

void *ded(void *args)
{
	t_needed *life;

	life = args;
	while(*(life->died))
	{
		pthread_mutex_lock(&life->is_eating); 
		if(since_last_meal(life) <= life->death && *(life->died))
		{	
			*(life->died) = 0; 
			printf("philosopher %d is " "\033[0;30m" "ded" "\033[0m" ".\n", life->philosopher);
		}
		pthread_mutex_unlock(&life->is_eating); 
	}
	return (NULL);
}

void *test(void *args)
{
	t_forks *life;
	int sleeping;
	int eating;
	pthread_mutex_t *mutex[3];

	sleeping = 500;
	eating = 400;
	life = args;
	mutex[0] = &life->next->fork;
	mutex[1] = &life->fork;
	mutex[2] = &life->philosopher->is_eating;
	while(*(life->philosopher->died))
	{
		pthread_mutex_lock(mutex[0]); puts("eh");
		pthread_mutex_lock(mutex[1]);
		if(*(life->philosopher->died))
		{
			printf("philosopher %d is picking" "\033[0;31m" " first fork" "\033[0m" ".\n", life->philosopher->philosopher);
			printf("philosopher %d is picking" "\033[0;31m" " second fork" "\033[0m" ".\n", life->philosopher->philosopher);
			pthread_mutex_lock(mutex[2]);
			printf("philosopher %d is" "\033[0;32m" " eating" "\033[0m" ".\n", life->philosopher->philosopher); 
			usleep(eating * 1000);
			pthread_mutex_unlock(mutex[2]);
		}
		pthread_mutex_unlock(mutex[0]);
		pthread_mutex_unlock(mutex[1]);
		gettimeofday(&(life->philosopher->last_meal), NULL);
		if(*(life->philosopher->died))
		{
			printf("philosopher %d is " "\033[0;37m" "sleeping" "\033[0m" ".\n", life->philosopher->philosopher);
			usleep(sleeping * 1000);
		}
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
		pthread_detach(idd[philo_count - 1]);
	}
	return (0);
}