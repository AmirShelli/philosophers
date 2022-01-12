#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

enum options
{
	num_of_philosophers,
	time_to_die,
	time_to_eat,
	time_to_sleep,
	must_eat
};

typedef struct s_philosopher
{
	struct s_philosopher *next;
	int 			philosopher;
	pthread_t 		philo_id;
	pthread_t 		death_id;
	pthread_mutex_t is_eating;
	struct timeval 	last_meal;
	pthread_mutex_t fork;
	int 			fork_freed;
}	t_philosopher;

typedef struct s_kitchen
{
	t_philosopher	*philosopher;
	struct timeval	starting_time;
	int 			*someone_died;
	int				options[6];
} t_kitchen;

t_kitchen 		*get_next_odd(t_kitchen *forks);
t_kitchen 		*get_next_even(t_kitchen *forks);


int 			*parsed(int argc, char *argv[]);

int				ft_atoi(const char *str);
t_philosopher 	*life_init(int philosopher, int *died, struct timeval starting_time);
void			new_philosopher(int philosopher, int *died, t_kitchen **head, struct timeval starting_time);
#endif