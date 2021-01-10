/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:56:42 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/10 20:50:02 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

void	exit_thread(const int phl_numb)
{
	g_live_tm = -1;
	g_run = false;
	kill(philo[phl_numb], 0);
}

void	philo_life(void *data)
{
	const int	phl_numb = (int)data;
	int			phl_eated;
	pthread_t	check;

	sleep_untill(g_start_time);
	pthread_create(&check, NULL, check_death, (void*)(long)phl_numb);
	pthread_detach(check);
	g_live_tm = get_time();
	phl_eated = 0;
	while (g_live)
	{
		print(phl_numb + 1, "is thinking", g_live);
		lock_fork(phl_numb);
		print(phl_numb + 1, "is eating", g_live);
		phl_eated++;
		g_live_tm = get_time();
		ft_sleep(g_phl_cfg.tm_to_eat);
		sem_post(g_forks);
		if (phl_eated >= g_phl_cfg.each_must_eat && g_phl_cfg.each_must_eat > 0)
			exit_thread(phl_numb);
		print(phl_numb + 1, "is sleeping", g_live);
		ft_sleep(g_phl_cfg.tm_to_sleep);
	}
	exit_thread(phl_numb);
}

void	clear_threads(void)
{
	int i;

	g_live = false;
	i = 0;
	waitpid(philo[i], NULL, 0);
	sem_close(g_forks);
	sem_close(g_print_lock);
	sem_unlink("print");
	sem_unlink("forks");
}

void	*check_death(void *i_addr)
{
	bool	run;
	const	int i = (int)i_addr;
	int		philo_numb;

	run = true;
	while (run)
	{
		run = false;	
		if (get_time() - g_live_tm > g_phl_cfg.tm_to_die)
		{
			print(i + 1, "died", g_live);
			philo_numb = 0;
			while(i < g_phl_cfg.nbr_of_philos)
				kill(philo[philo_numb++], 0);
			break ;
		}
		run = run || g_run;
	}
	return (NULL);
}

void	thread_init(void)
{
	int		i;

	g_start_time = get_time();
	g_live = true;
	sem_unlink("print");
	sem_unlink("forks");
	g_forks = sem_open("forks", O_CREAT, 0644, g_phl_cfg.nbr_of_philos / 2);
	g_print_lock = sem_open("print", O_CREAT, 0644, 1);
	i = 0;
	while (i < g_phl_cfg.nbr_of_philos)
	{
		g_run = true;
		philo[i] = fork();
		if (philo[i] == 0)
			philo_life((void*)(long)i);
		i++;
	}
	clear_threads();
}
