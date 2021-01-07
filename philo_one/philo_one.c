/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:02:15 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/07 20:38:03 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo_one.h"
#include <stdbool.h>
#include <unistd.h>

int		check_data(int ac)
{
	if (g_phl_cfg.nbr_of_philos < 1 || g_phl_cfg.nbr_of_philos > 200)
		return (1);
	else if (g_phl_cfg.tm_to_die < 60)
		return (1);
	else if (g_phl_cfg.tm_to_eat < 60)
		return (1);
	else if (g_phl_cfg.tm_to_sleep < 60)
		return (1);
	else if (g_phl_cfg.each_must_eat < 1 && ac == 6)
		return (1);
	else
		return (0);
}

int		init_data(int ac, char **av)
{
	g_phl_cfg.nbr_of_philos = ft_atoi(av[1]);
	g_phl_cfg.tm_to_die = ft_atoi(av[2]);
	g_phl_cfg.tm_to_eat = ft_atoi(av[3]);
	g_phl_cfg.tm_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		g_phl_cfg.each_must_eat = ft_atoi(av[5]);
	else
		g_phl_cfg.each_must_eat = -1;
	return (check_data(ac));
}

int		main(int ac, char *av[])
{
	pthread_mutex_init(&g_print_mutex, NULL);
	if (ac < 5 || ac > 6)
		write(1, "Too many or low arguments\n", 27);
	else if ((init_data(ac, av)))
		write(1, "Arguments not right\n", 21);
	else
		thread_init();
	return (0);
}
