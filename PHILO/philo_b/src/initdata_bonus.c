#include "../inc/philo_bonus.h"

void	ft_init_data(t_info *x)
{
	x->id = malloc((x->totph + 1) * sizeof(int));
	memset(x->id, 0, x->totph + 1);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/die");
	x->forks = sem_open("/forks", O_CREAT, 0644, x->totph);
	x->print = sem_open("/print", O_CREAT, 0644, 1);
	x->die = sem_open("/die", O_CREAT, 0644, 1);
	x->start = sem_open("/start", O_CREAT, 0644, 0);
}

void	ft_free_info(t_info *x)
{
	free(x->id);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/die");
	sem_unlink("/start");
	sem_close(x->forks);
	sem_close(x->print);
	sem_close(x->die);
	sem_close(x->start);
}
