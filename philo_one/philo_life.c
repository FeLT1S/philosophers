/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:56:42 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/07 21:34:43 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void	sleep_untill(int ms_stamp)
{
	while (true)
	{
		if (get_time() >= ms_stamp)
			return ;
		usleep(100);
	}
}

int		phl_eat(int phl_eated, int phl_numb)
{
	if (g_phl_cfg.each_must_eat > phl_eated + 1 || g_phl_cfg.each_must_eat < 0)
		phl_eated++;
	else
		g_live = 0;
	print(phl_numb + 1, "is eating", g_live);
	return (phl_eated);
}

void	*philo_life(void *data)
{
	const int	phl_numb = (int)data;
	const int	l_fork = take_lfork(phl_numb);
	const int	r_fork = take_rfork(phl_numb);
	int			phl_eated;

	sleep_untill(g_start_time);
	if ((phl_numb % 2))
		usleep(100);
	g_live_tm[phl_numb] = get_time();
	phl_eated = 0;
	while (g_live)
	{
		print(phl_numb + 1, "is thinking", true);
		lock_fork(l_fork, r_fork, phl_numb);
		phl_eated = phl_eat(phl_eated, phl_numb);
		g_live_tm[phl_numb] = get_time();
		ft_sleep(g_phl_cfg.tm_to_eat);
		unlock_fork(l_fork, r_fork);
		print(phl_numb + 1, "is sleeping", true);
		ft_sleep(g_phl_cfg.tm_to_sleep);
	}
	return (NULL);
}

void	check_death(void)
{
	int i;

	i = 0;
	while (g_live)
	{
		i = 0;
		while (i < g_phl_cfg.nbr_of_philos && g_live)
		{
			if (get_time() - g_live_tm[i] > g_phl_cfg.tm_to_die)
			{
				print(i + 1, "died", false);
				g_live = false;
				break ;
			}
			i++;
		}
	}
	i = 0;
	while (i < g_phl_cfg.nbr_of_philos)
	{
		pthread_mutex_destroy(&g_fork[i]);
		i++;
	}
}

void	thread_init(void)
{
	int		i;

	memset(g_live_tm, 0, sizeof(bool) * g_phl_cfg.nbr_of_philos);
	g_start_time = get_time() + 1000;
	i = 0;
	g_live = true;
	while (i < g_phl_cfg.nbr_of_philos)
	{
		pthread_mutex_init(&g_fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < g_phl_cfg.nbr_of_philos)
	{
		pthread_create(&g_philos[i], NULL, philo_life, (void*)(long)i);
		pthread_detach(g_philos[i]);
		i++;
	}
	check_death();
}
