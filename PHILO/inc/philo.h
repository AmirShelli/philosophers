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

t_kitchen		*create_kitchen(int argc, char *argv[]);
void			new_philosopher(int philo_counter, t_philosopher **head);

int				get_time_passed(t_kitchen *life, struct timeval *time);
long int		since_last_meal(t_kitchen *life);

void 			*check_death(void *args);
void			*routine(void *args);

t_philosopher 		*get_next_fork(t_kitchen *forks, int flag);
int				ft_atoi(const char *str);
#endif