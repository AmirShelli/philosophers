#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_needed
{
	int arguments[6];
	pthread_mutex_t fork[2];
	int eating;
	int sleeping;
	int philosopher;
}	t_needed;

int *parsed(int argc, char *argv[]);

int		ft_atoi(const char *str);

#endif