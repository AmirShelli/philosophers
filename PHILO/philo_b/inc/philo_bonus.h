#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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

enum e_options
{
	num_of_philosophers,
	time_to_die,
	time_to_eat,
	time_to_sleep,
	must_eat
};



typedef struct s_info
{
	int				*id;
	size_t			ph;
	long			timestart;
	size_t				*options;
	size_t			timeincrease;
	sem_t			*forks;	
	sem_t			*print;
	sem_t			*die;
	sem_t			*start;
}	t_info;
int		ft_atoi(const char *str);
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
