#include "../../inc/philo.h"
#include <stdio.h>

t_philosopher *get_next_fork(t_kitchen *kitchen, int flag)
{
	t_philosopher *temp;

	temp = kitchen->philosopher;
	while(1)
	{	
		if(!((temp->philosopher % 2) - flag) && temp->fork_freed)
			return(temp);
		temp = temp->next;
	}
	return (NULL);
}