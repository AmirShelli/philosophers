/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkinput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharghaz <bharghaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:21:39 by bharghaz          #+#    #+#             */
/*   Updated: 2022/01/25 22:21:39 by bharghaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_atoi(const char *str)
{
	int	out;
	int	i;
	int	neg;

	neg = 1;
	i = 0;
	out = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{	
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (out * neg);
		out = out * 10 + (str[i] - '0');
		i++;
	}
	return (out * neg);
}

static int	ft_check_input(int argc, char **argv)
{
	int	i;
	int	len;

	if (argc > 6 || argc < 5)
	{
		printf("Error: Arguments\n");
		return (0);
	}
	i = 0;
	while (argv[++i])
	{
		len = -1;
		while (argv[i][++len])
		{
			if (!ft_isdigit(argv[i][len]))
			{
				printf("Error: Wrong type of argument\n");
				return (0);
			}
		}
	}
	return (1);
}

int	set_data(t_info *x, char **argv, int argc)
{
	if (!ft_check_input(argc, argv))
		return (0);
	x->totph = (size_t) ft_atoi(argv[1]);
	x->timeincrease = (size_t) ft_atoi(argv[2]);
	x->timetoeat = (size_t) ft_atoi(argv[3]);
	x->timetosleep = (size_t) ft_atoi(argv[4]);
	if (x->totph == 0)
	{
		printf("Error: Wrong number of philosophers\n");
		return (0);
	}
	if (argc == 6)
		x->eattimes = (size_t) ft_atoi(argv[5]);
	else
		x->eattimes = -1;
	return (1);
}

int	ft_onephilo(t_info x)
{
	if (x.totph == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(x.timeincrease * 1000);
		printf("%lu 1 died\n", x.timeincrease);
		return (1);
	}
	return (0);
}
