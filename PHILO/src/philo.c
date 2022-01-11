#include "../inc/philo.h"
// #include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>


int get_time_passed(t_needed *life, struct timeval time)
{
	long long int ending_time;
	long long int starting_time;
	ending_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	starting_time = (life->starting_time.tv_sec * 1000) + (life->starting_time.tv_usec / 1000);
	return (ending_time - starting_time);
}

long int since_last_meal(t_needed *life)
{
	struct timeval current_time;
	long int current;
	long int meal_time;

	meal_time = get_time_passed(life, life->last_meal);
	gettimeofday(&current_time, NULL);
	current = get_time_passed(life, current_time);
	return (current - meal_time);
}

t_needed *life_init(int philosopher, int *died, struct timeval starting_time)
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
	sample->starting_time = starting_time;
	sample->last_meal = starting_time;
	sample->died = died;
	sample->philosopher = philosopher;
	sample->arguments[i - 1] = -1;
	// sample->sleeping = 0;
	// sample->eating = 0;
	sample->death = 150;
	return (sample);
}

void *ded(void *args)
{
	t_needed *life;
	struct timeval current;

	life = args;
	while(*(life->died))
	{
		pthread_mutex_lock(&life->is_eating); 
		if(since_last_meal(life) >= life->death && *(life->died))
		{	
			*(life->died) = 0; 
			gettimeofday(&current, NULL);
			printf("%d %d is " "\033[0;30m" "ded" "\033[0m" ".\n",
				get_time_passed(life, current), life->philosopher);
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
	t_forks *mutex[3];

	sleeping = 1;
	eating = 4;
	life = args;
	mutex[0] = get_next_even(life);
	mutex[1] = get_next_odd(life);
	while(*(life->philosopher->died))
{
		pthread_mutex_lock(&mutex[0]->fork);
		mutex[0]->free = 0;
		pthread_mutex_lock(&mutex[1]->fork);
		mutex[1]->free = 0;
		pthread_mutex_lock(&life->philosopher->is_eating);
		if(*(life->philosopher->died))
		{
			printf("philosopher %d is picking" "\033[0;31m" " first fork" "\033[0m" ".\n", life->philosopher->philosopher);
			printf("philosopher %d is picking" "\033[0;31m" " second fork" "\033[0m" ".\n", life->philosopher->philosopher);
			printf("philosopher %d is" "\033[0;32m" " eating" "\033[0m" ".\n", life->philosopher->philosopher); 
			usleep(eating * 100);
			gettimeofday(&(life->philosopher->last_meal), NULL);
			pthread_mutex_unlock(&life->philosopher->is_eating);
		}
		pthread_mutex_unlock(&mutex[0]->fork);
		mutex[0]->free = 1;
		pthread_mutex_unlock(&mutex[1]->fork);
		mutex[1]->free = 1;
		// printf("%d last meal is at %ld\n", life->philosopher->philosopher, (long)(life->philosopher->last_meal.tv_sec));
		if(*(life->philosopher->died))
		{
			printf("philosopher %d is " "\033[0;37m" "sleeping" "\033[0m" ".\n", life->philosopher->philosopher);
			usleep(sleeping * 10);
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
	struct timeval starting_time;
	int philos = 6;
	pthread_t id[philos];
	pthread_t idd[philos];
	int philo_count;
	t_forks *forks;
	int died = 1;

	// args = parsed(argc, argv); // don't forget to free.
	forks = NULL;
	philo_count = 0;
	gettimeofday(&starting_time, NULL);
	while(++philo_count < philos)
	{	
		new_philosopher(philo_count, &died, &forks, starting_time); 
		pthread_create(&id[philo_count - 1], NULL, &test, forks);
		pthread_create(&idd[philo_count - 1], NULL, &ded, forks->philosopher);
	}

	philo_count = 0;
	while(++philo_count < philos)
	{	
		pthread_join(id[philo_count - 1], NULL);
		pthread_detach(idd[philo_count - 1]);
	}
	return (0);
}