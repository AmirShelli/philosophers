#include "../../inc/philo.h"


void create_kitchen(t_kitchen *kitchen, int argc, char *argv[])
{
	int i;

	i = 1;
	kitchen->philosopher = NULL;
	gettimeofday(&kitchen->starting_time, NULL);
	kitchen->someone_died = 0;
	while(--argc)
	{
		kitchen->options[i - 1] = atoi(argv[i++]); // !!! not my atoi !!! delete later
		// i++;
	}
	kitchen->options[i - 1] = -1;
}

void	new_philosopher(int philo_counter, t_philosopher **head)
{
	t_philosopher *sample;
	t_philosopher *temp;

	sample = malloc(sizeof(t_philosopher));
	temp = *head;
	sample->next = *head;
	sample->philosopher = philo_counter + 1;
	sample->philo_id = philo_counter;
	sample->death_id = philo_counter;
	
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
