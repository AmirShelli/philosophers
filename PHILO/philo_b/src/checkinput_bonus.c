#include "../inc/philo_bonus.h"

int	set_data(t_info *x, char **argv, int argc)
{
	int i;

	i = -1;
	while (++i < argc - 1)
		x->options[i] = ft_atoi(argv[i + 1]);
	if (argc == 6)
	{	
		x->options[must_eat] *= x->options[num_of_philosophers];
		if(x->options[must_eat] + 1 <= 0)
			return (0);
	}
	else
		x->options[must_eat] = -1;
	if (x->options[num_of_philosophers] < 1 || 
		x->options[num_of_philosophers] > 200 ||
		x->options[time_to_die]  < 60 || 
		x->options[time_to_eat] < 60 || 
		x->options[time_to_sleep] < 60||
		(argc != 5 && argc != 6))
			return (0);
	return (1);
}

int	ft_onephilo(t_info x)
{
	if (x.options[num_of_philosophers] == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(x.timeincrease * 1000);
		printf("%lu 1 died\n", x.timeincrease);
		return (1);
	}
	return (0);
}
