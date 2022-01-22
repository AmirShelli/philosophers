#include "../../inc/philo.h"

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
