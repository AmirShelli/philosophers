#include "../inc/philo.h"
#include <stdio.h>

void *check_death(void *args)
{
	t_kitchen *life;

	life = args;
	while(*(life->someone_died))
	{
		pthread_mutex_lock(&life->philosopher->is_eating); 
		if(since_last_meal(life) >= life->options[time_to_die] && *(life->someone_died))
		{	
			*(life->someone_died) = 0; 
			printf("%d\t%d " "\033[0;45m" "someone_died" "\033[0m" ".\n",
				get_time_passed(life, NULL), life->philosopher->philosopher);
		}
		pthread_mutex_unlock(&life->philosopher->is_eating); 
	}
	return (NULL);
}

void *routine(void *args)
{
	t_kitchen		*life;
	t_philosopher	*mutex[3];

	life = args;
	mutex[0] = get_next_fork(life, 0);
	mutex[1] = get_next_fork(life, 1);
	while(*(life->someone_died))
	{
		pthread_mutex_lock(&mutex[0]->fork);
		mutex[0]->fork_freed = 0;
		pthread_mutex_lock(&mutex[1]->fork);
		mutex[1]->fork_freed = 0;
		pthread_mutex_lock(&life->philosopher->is_eating);
		if(*(life->someone_died))
		{	
			printf("%d\t%d has " "\033[0;31m" "taken a fork" "\033[0m" ".\n", get_time_passed(life, NULL), life->philosopher->philosopher);
			printf("%d\t%d has " "\033[0;31m" "taken a fork" "\033[0m" ".\n", get_time_passed(life, NULL), life->philosopher->philosopher);
			printf("%d\t%d is" "\033[0;32m" " eating" "\033[0m" ".\n",get_time_passed(life, NULL), life->philosopher->philosopher); 
			usleep(life->options[time_to_eat]);
			gettimeofday(&(life->philosopher->last_meal), NULL);
			pthread_mutex_unlock(&life->philosopher->is_eating);
		}
		pthread_mutex_unlock(&mutex[0]->fork);
		mutex[0]->fork_freed  = 1;
		pthread_mutex_unlock(&mutex[1]->fork);
		mutex[1]->fork_freed = 1;
		if(*(life->someone_died))
		{
			printf("%d\t%d is " "\033[0;37m" "sleeping" "\033[0m" ".\n", get_time_passed(life, NULL), life->philosopher->philosopher);
			usleep(life->options[time_to_sleep]);
		}
		if(*(life->someone_died))
			printf("%d\t%d is " "\033[0;35m" "thinking" "\033[0m" ".\n", get_time_passed(life, NULL), life->philosopher->philosopher);
	}
	return(NULL);
}
