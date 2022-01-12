#include "../inc/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
// #include <bits/types/struct_timeval.h>

// void show_insides()


int	get_time_passed(t_kitchen *life, struct timeval *time)
{
	long long int	ending_time;
	long long int	starting_time;
	struct timeval	temp;

	starting_time = (life->starting_time.tv_sec * 1000) + (life->starting_time.tv_usec / 1000);
	if (time)
		ending_time = (time->tv_sec * 1000) + (time->tv_usec / 1000);
	else 
	{
		gettimeofday(&temp, NULL);
		ending_time = (temp.tv_sec * 1000) + (temp.tv_usec / 1000);
	}
	return (ending_time - starting_time);
}

long int	since_last_meal(t_kitchen *life)
{
	long int current;
	long int meal_time;

	meal_time = get_time_passed(life, &(life->philosopher->last_meal));
	current = get_time_passed(life, NULL);
	return (current - meal_time);
}

int	main(int argc, char *argv[])
{
	int				philosopher;
	t_kitchen 		*kitchen;
	t_philosopher	*philo_head;

	//check for errors
	philosopher = 0;
	kitchen = create_kitchen(argc, argv);
	philo_head = kitchen->philosopher;
	while(philosopher++ < kitchen->options[num_of_philosophers])
	{	
		pthread_create(&(kitchen->philosopher->philo_id), NULL, &routine, kitchen);
		// pthread_create(&(kitchen->philosopher->death_id), NULL, &check_death, kitchen);
		new_philosopher(philosopher, &kitchen->philosopher);
	}

	philosopher = 0;
	kitchen->philosopher = philo_head;
	while(philosopher++ < kitchen->options[num_of_philosophers])
	{	
		pthread_join(kitchen->philosopher->death_id, NULL);
		// pthread_detach(kitchen->philosopher->death_id);
	}
	// free philosophers list and the kitchen as well
	return (0);
}