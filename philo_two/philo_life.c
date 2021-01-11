/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:56:42 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/11 18:14:28 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void	*exit_thread(const int phl_numb)
{
	g_live_tm[phl_numb] = -1;
	g_run[phl_numb] = false;
	return (NULL);
}

void	*philo_life(void *data)
{
	const int	phl_numb = (int)data;
	int			phl_eated;

	sleep_untill(g_start_time);
	g_live_tm[phl_numb] = get_time();
	phl_eated = 0;
	while (g_live)
	{
		print(phl_numb + 1, "is thinking", g_live);
		lock_fork(phl_numb);
		print(phl_numb + 1, "is eating", g_live);
		phl_eated++;
		g_live_tm[phl_numb] = get_time();
		ft_sleep(g_phl_cfg.tm_to_eat);
		sem_post(g_forks);
		if (phl_eated >= g_phl_cfg.each_must_eat && g_phl_cfg.each_must_eat > 0)
			return (exit_thread(phl_numb));
		print(phl_numb + 1, "is sleeping", g_live);
		ft_sleep(g_phl_cfg.tm_to_sleep);
	}
	return (exit_thread(phl_numb));
}

void	clear_threads(t_philos *philos)
{
	int i;

	g_live = false;
	i = 0;
	while (i < g_phl_cfg.nbr_of_philos)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
	sem_close(g_forks);
	sem_close(g_print_lock);
	sem_unlink("print");
	sem_unlink("forks");
}

void	check_death(t_philos *philos)
{
	int		i;
	bool	run;

	i = 0;
	run = true;
	while (run)
	{
		i = 0;
		run = false;
		while (i < g_phl_cfg.nbr_of_philos)
		{
			if (get_time() - g_live_tm[i] > g_phl_cfg.tm_to_die)
			{
				print(i + 1, "died", g_live);
				g_live = false;
				break ;
			}
			run = run || g_run[i];
			i++;
		}
	}
	clear_threads(philos);
}

void	thread_init(void)
{
	int			i;
	t_philos	philos[MAX_PHLS];

	memset(g_live_tm, 0, sizeof(int) * g_phl_cfg.nbr_of_philos);
	g_start_time = get_time() + 1000;
	g_live = true;
	sem_unlink("print");
	sem_unlink("forks");
	g_forks = sem_open("forks", O_CREAT, 0644, g_phl_cfg.nbr_of_philos / 2);
	g_print_lock = sem_open("print", O_CREAT, 0644, 1);
	i = 0;
	while (i < g_phl_cfg.nbr_of_philos)
	{
		g_run[i] = true;
		pthread_create(&philos[i], NULL, philo_life, (void*)(long)i);
		i++;
	}
	check_death(philos);
}
