#include "../../inc/philo.h"
#include <stdio.h>

t_forks *get_next_even(t_forks *forks)
{
	t_forks *temp;

	temp = forks;
	while(1)
	{	
		if(!(temp->philosopher->philosopher % 2) && temp->free)
			return(temp);
		temp = temp->next;
	}
	return (NULL);
}

t_forks *get_next_odd(t_forks *forks)
{
	t_forks *temp;

	temp = forks;
	while(1)
	{	
		if((temp->philosopher->philosopher % 2) && temp->free)
			return(temp);
		temp = temp->next;
	}
	return (NULL);
}