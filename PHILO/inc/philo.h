#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_needed
{
	int arguments[6];

	int eating;
	int sleeping;
	int philosopher;
	struct timeval last_meal;
	pthread_mutex_t is_eating;
	int death;
	int *died;
}	t_needed;

typedef struct s_forks
{
	pthread_mutex_t fork;
	struct s_forks *next; 
	t_needed *philosopher;
} t_forks;

int *parsed(int argc, char *argv[]);

int		ft_atoi(const char *str);
t_needed *life_init(int philosopher, int *died);
// pthread_mutex_t *find_fork(int p, t_forks *f);
void	new_philosopher(int p, int *died, t_forks **f);
#endif