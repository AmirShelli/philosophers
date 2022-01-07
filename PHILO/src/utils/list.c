#include "../../inc/philo.h"
#include <pthread.h>

// pthread_mutex_t	*find_fork(int philosopher, t_forks *forks)
// {
// 	t_forks *temp;

// 	temp = forks;
// 	while (temp->next)
// 	{
// 		if(philosopher == temp->philosopher)
// 			return(&temp->fork);
// 		temp = temp->next;
// 	}
// 	return (NULL);
// }

void	new_philosopher(int philosopher, int *died, t_forks **head)
{
	t_forks *sample;
	t_forks *temp;

	sample = malloc(sizeof(t_forks));
	temp = *head;
	sample->next = *head;
	sample->philosopher = life_init(philosopher, died);
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