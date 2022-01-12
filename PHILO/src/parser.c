/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharghaz <bharghaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 22:17:46 by bharghaz          #+#    #+#             */
/*   Updated: 2022/01/12 20:04:02 by bharghaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int *parsed(int argc, char *argv[])
{
	int *argument;
	int i;

	i = 1;
	argument = malloc(argc + 1);
	while(--argc)
	{
		argument[i - 1] = atoi(argv[i]); // !!! not my atoi !!! delete later
		i++;
	}
	argument[i - 1] = -1;
	return(argument);
}