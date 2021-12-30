#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_needed
{
	int arguments[6];

	int eating;
	int sleeping;
	int philosopher;
}	t_needed;


typedef struct s_hello
{
	pthread_mutex_t fork[2];
	t_needed *life;
}	t_hello;
int *parsed(int argc, char *argv[]);

int		ft_atoi(const char *str);

#endif