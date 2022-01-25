/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharghaz <bharghaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:21:50 by bharghaz          #+#    #+#             */
/*   Updated: 2022/01/25 22:21:56 by bharghaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <semaphore.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>

typedef struct s_info
{
	int				*id;
	size_t			ph;
	long			timestart;
	long			timedie;
	size_t			timetoeat;
	size_t			timetosleep;
	size_t			timeincrease;
	size_t			eattimes;
	size_t			totph;
	sem_t			*forks;	
	sem_t			*print;
	sem_t			*die;
	sem_t			*start;
}	t_info;

int		set_data(t_info *x, char **argv, int argc);
void	ft_init_data(t_info *x);
void	ft_free_info(t_info *x);
size_t	ft_checktime(long ref);
void	ft_print(char *str, t_info *z);
void	ft_isdead(t_info *z);
void	ft_eat(t_info *z);
void	ft_sleep(t_info *z);
int		ft_onephilo(t_info x);

#endif
