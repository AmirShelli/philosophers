#include "../../inc/philo.h"
#include <stdio.h>


t_kitchen *create_kitchen(int argc, char *argv[])
{
	t_kitchen *kitchen;
	int i;

	i = 1;
	kitchen = malloc(sizeof(t_kitchen));
	kitchen->someone_died = malloc(sizeof(int));
	*kitchen->someone_died = 1;
	while(--argc)
	{
		kitchen->options[i - 1] = atoi(argv[i]); // !!! not my atoi !!! delete later
		i++;
	}
	kitchen->options[i - 1] = -1;
	gettimeofday(&kitchen->starting_time, NULL);
	kitchen->philosopher = NULL;
	new_philosopher(0, &kitchen->philosopher);
	return (kitchen);
}

void	new_philosopher(int philo_counter, t_philosopher **head)
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
