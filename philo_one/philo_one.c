/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:02:15 by jiandre           #+#    #+#             */
/*   Updated: 2020/12/26 17:15:52 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo_one.h"
#include <stdbool.h>
#include <unistd.h>

int		init_data(int ac, char **av)
{
	if ((phl_cfg.nbr_of_philos = ft_atoi(av[1])) < 1 ||
	phl_cfg.nbr_of_philos > 200)
		return (1);
	if ((phl_cfg.tm_to_die = ft_atoi(av[2])) < 1)
		return (1);
	if ((phl_cfg.tm_to_eat = ft_atoi(av[3])) < 1)
		return (1);
	if ((phl_cfg.tm_to_sleep = ft_atoi(av[4])) < 1)
		return (1);
	if (ac == 6 && (phl_cfg.each_must_eat = ft_atoi(av[5])) < 1)
		return (1);
	return (0);
}

int		main(int ac, char *av[])
{
	pthread_mutex_init(&print_mutex, NULL);
	if (ac < 5 || ac > 6)
		print("Too many or low arguments", 0, NULL);
	else if ((init_data(ac, av)))
		print("Arguments not right", 0, NULL);
	else
		thread_init(&phl_cfg);
	return(0);
}