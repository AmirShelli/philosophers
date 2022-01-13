#include "../../inc/philo.h"
#include <stdio.h>


t_dinning *create_dinning(int argc, char *argv[])
{
	t_dinning *dinning;
	int i;

	i = 1;
	dinning = malloc(sizeof(t_dinning));
	dinning->someone_died = malloc(sizeof(int));
	*dinning->someone_died = 1;
	while(--argc)
	{
		dinning->options[i - 1] = atoi(argv[i]); // !!! not my atoi !!! delete later
		i++;
	}
	dinning->options[i - 1] = -1;
	gettimeofday(&dinning->starting_time, NULL);
	return (dinning);
}

void	new_philosopher(int philo_counter, t_dinning *dinning, t_philosopher **head)
{
	t_philosopher *sample;
	t_philosopher *temp;

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
