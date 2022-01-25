#include "../../inc/philo.h"

void	*check_death(void *args)
{
	t_philosopher	*life;

	life = args;
	while (*(life->dinning->someone_died))
	{
		pthread_mutex_lock(&life->is_eating);
		if ((since_last_meal(life) >= life->dinning->options[time_to_die] ||
			!life->dinning->options[must_eat]) &&
			*(life->dinning->someone_died))
		{	
			*(life->dinning->someone_died) = 0;
			printf("%d\t%d " "\033[0;45m" "died" "\033[0m" ".\n",
				get_time_passed(life->dinning, NULL), life->philosopher);
			exit(0);
		}
		pthread_mutex_unlock(&life->is_eating);
	}
	return (NULL);
}

static void	eat(t_philosopher *life)
{
	t_philosopher	*mutex[3];

	mutex[0] = get_next_fork(life, 0);
	mutex[1] = get_next_fork(life, 1);
	pthread_mutex_lock(&mutex[0]->fork);
	mutex[0]->fork_freed = 0;
	pthread_mutex_lock(&mutex[1]->fork);
	mutex[1]->fork_freed = 0;
	pthread_mutex_lock(&life->is_eating);
	if (*(life->dinning->someone_died))
	{
	printf("%d\t%d has " "\033[0;31m" "taken a fork" "\033[0m" ".\n",
		get_time_passed(life->dinning, NULL), life->philosopher);
	printf("%d\t%d has " "\033[0;31m" "taken a fork" "\033[0m" ".\n",
		get_time_passed(life->dinning, NULL), life->philosopher);
	gettimeofday(&(life->last_meal), NULL);
	printf("%d\t%d is" "\033[0;32m" " eating" "\033[0m" ".\n",
		get_time_passed(life->dinning, NULL), life->philosopher);
	}
	usleep(life->dinning->options[time_to_eat] * 1000);
	life->dinning->options[must_eat]--;
	pthread_mutex_unlock(&life->is_eating);
	pthread_mutex_unlock(&mutex[0]->fork);
	mutex[0]->fork_freed = 1;
	pthread_mutex_unlock(&mutex[1]->fork);
	mutex[1]->fork_freed = 1;
}

void	*routine(void *args)
{
	t_philosopher		*life;

	life = args;
	while (*(life->dinning->someone_died))
	{
		if (*(life->dinning->someone_died))
			eat(life);
		if (*(life->dinning->someone_died))
		{
			printf("%d\t%d is " "\033[0;37m" "sleeping" "\033[0m" ".\n",
				get_time_passed(life->dinning, NULL), life->philosopher);
			usleep(life->dinning->options[time_to_sleep] * 1000);
		}
		if (*(life->dinning->someone_died))
			printf("%d\t%d is " "\033[0;35m" "thinking" "\033[0m" ".\n",
				get_time_passed(life->dinning, NULL), life->philosopher);
	}
	return (NULL);
}
