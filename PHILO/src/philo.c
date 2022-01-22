#include "../inc/philo.h"

int	get_time_passed(t_dinning *life, struct timeval *time)
{
	long long int	ending_time;
	long long int	starting_time;
	struct timeval	temp;

	starting_time = (life->starting_time.tv_sec * 1000)
		+ (life->starting_time.tv_usec / 1000);
	if (time)
		ending_time = (time->tv_sec * 1000) + (time->tv_usec / 1000);
	else
	{
		gettimeofday(&temp, NULL);
		ending_time = (temp.tv_sec * 1000) + (temp.tv_usec / 1000);
	}
	return (ending_time - starting_time);
}

long int	since_last_meal(t_philosopher *life)
{
	long int	current;
	long int	meal_time;

	meal_time = get_time_passed(life->dinning, &(life->last_meal));
	current = get_time_passed(life->dinning, NULL);
	return (current - meal_time);
}

int	main(int argc, char *argv[])
{
	int				number_of_philo;
	t_dinning		*dinning;
	t_philosopher	*philosopher;

	dinning = create_dinning(argc, argv);
	if(!dinning)
		return(printf("Error.\n"));
	philosopher = NULL;
	number_of_philo = 0;
	while (number_of_philo++ < dinning->options[num_of_philosophers])
	{	
		new_philosopher(number_of_philo - 1, dinning, &philosopher);
		pthread_create(&(philosopher->philo_id), NULL, &routine, philosopher);
		pthread_create(&(philosopher->death_id), NULL, &check_death,
			philosopher);
	}
	number_of_philo = 0;
	while (number_of_philo++ < dinning->options[num_of_philosophers])
	{
		pthread_join(philosopher->philo_id, NULL);
		pthread_join(philosopher->death_id, NULL);
	}
	return (0);
}
