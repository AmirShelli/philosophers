/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharghaz <bharghaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:05:37 by bharghaz          #+#    #+#             */
/*   Updated: 2022/01/25 22:05:39 by bharghaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_status(t_phil *phil, char *msg)
{
	if (phil->args->exit == 0 && phil->args->finish == 0)
		printf("%ld %d %s\n", get_time(phil->args), phil->number, msg);
}

int	error_return(char *msg)
{
	printf("%s\n", msg);
	return (1);
}

int	error_clean(char *msg, t_args *args)
{
	printf("%s\n", msg);
	free(args->forks);
	free(args->phils);
	return (1);
}

long	get_time(t_args *args)
{
	struct timeval	t;
	long			current;

	gettimeofday(&t, NULL);
	current = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (current - args->timer_start);
}

long	get_start_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}
