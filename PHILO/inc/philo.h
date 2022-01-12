#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_needed
{
	int arguments[6];

	int eating;
	int sleeping;
	int philosopher;
	pthread_mutex_t is_eating;
	int death;
	int *died;
	struct timeval last_meal;
	struct timeval starting_time;
}	t_needed;

typedef struct s_forks
{
	pthread_mutex_t fork;
	int free;
	struct s_forks *next; 
	t_needed *philosopher;
} t_forks;

t_forks 	*get_next_odd(t_forks *forks);
t_forks 	*get_next_even(t_forks *forks);


int 		*parsed(int argc, char *argv[]);

int			ft_atoi(const char *str);
t_needed 	*life_init(int philosopher, int *died, struct timeval starting_time);
void		new_philosopher(int philosopher, int *died, t_forks **head, struct timeval starting_time);
#endif