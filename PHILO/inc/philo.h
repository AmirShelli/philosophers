#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

enum e_options
{
	num_of_philosophers,
	time_to_die,
	time_to_eat,
	time_to_sleep,
	must_eat
};

typedef struct s_dinning
{
	struct timeval	starting_time;
	int				*someone_died;
	int				options[6];
}	t_dinning;

typedef struct s_philosopher
{
	struct s_philosopher	*next;
	int						philosopher;
	pthread_t				philo_id;
	pthread_t				death_id;
	pthread_mutex_t			is_eating;
	struct timeval			last_meal;
	pthread_mutex_t			fork;
	int						fork_freed;
	t_dinning				*dinning;
}	t_philosopher;

t_dinning		*create_dinning(int argc, char *argv[]);
void			new_philosopher(int philo_counter, t_dinning *dinning,
					t_philosopher **head);

int				get_time_passed(t_dinning *life, struct timeval *time);
long int		since_last_meal(t_philosopher *life);

void			*check_death(void *args);
void			*routine(void *args);

t_philosopher	*get_next_fork(t_philosopher *philosopher, int flag);
int				ft_atoi(const char *str);
#endif