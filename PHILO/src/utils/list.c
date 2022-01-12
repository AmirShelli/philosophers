#include "../../inc/philo.h"

void	new_philosopher(int philosopher, int *died, t_forks **head, struct timeval starting_time)
{
	t_forks *sample;
	t_forks *temp;

	sample = malloc(sizeof(t_forks));
	temp = *head;
	sample->next = *head;
	sample->philosopher = life_init(philosopher, died, starting_time);
	sample->free = 1;
	pthread_mutex_init(&sample->fork, NULL);
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