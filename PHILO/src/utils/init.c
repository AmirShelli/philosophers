#include "../../inc/philo.h"
#include <pthread.h>


void freeAll(t_philosopher *head)
{
	t_philosopher	*tmp;

	tmp = head;
	while (head->next != NULL)
    {
		pthread_mutex_destroy(&head->fork);
		pthread_mutex_destroy(&head->is_eating);
		tmp = head;
		head = head->next;
		free(tmp);
    }
}

t_philosopher	*get_next_fork(t_philosopher *philosopher, int flag)
{
	t_philosopher	*temp;

	temp = philosopher;
	while (1)
	{
		if (!((temp->philosopher % 2) - flag) && temp->fork_freed)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_dinning	*create_dinning(int argc, char *argv[])
{
	t_dinning	*dinning;
	int			i;

	i = -1;
	dinning = malloc(sizeof(t_dinning));
	dinning->someone_died = malloc(sizeof(int));
	*dinning->someone_died = 1;
	while (++i < argc - 1)
		dinning->options[i] = atoi(argv[i + 1]);
	if (argc == 6)
	{	
		dinning->options[must_eat] *= dinning->options[num_of_philosophers];
		if(dinning->options[must_eat] + 1 <= 0)
			return (NULL);
	}
	else
		dinning->options[must_eat] = -1;
	if (dinning->options[num_of_philosophers] < 1 || 
		dinning->options[num_of_philosophers] > 200 ||
		dinning->options[time_to_die]  < 60|| 
		dinning->options[time_to_eat] < 60 || 
		dinning->options[time_to_sleep] < 60||
		(argc != 5 && argc != 6))
			return (NULL);
	gettimeofday(&dinning->starting_time, NULL);
	return (dinning);
}

void	new_philosopher(int philo_counter, t_dinning *dinning,
						t_philosopher **head)
{
	t_philosopher	*sample;
	t_philosopher	*temp;

	sample = malloc(sizeof(t_philosopher));
	temp = *head;
	sample->next = *head;
	sample->philosopher = philo_counter + 1;
	pthread_mutex_init(&sample->is_eating, NULL);
	pthread_mutex_init(&sample->fork, NULL);
	sample->fork_freed = 1;
	sample->dinning = dinning;
	gettimeofday(&sample->last_meal, NULL);
	if (*head != NULL)
	{
		while (temp->next != *head)
			temp = temp->next;
		temp->next = sample;
	}
	else
		sample->next = sample;
	*head = sample;
}
