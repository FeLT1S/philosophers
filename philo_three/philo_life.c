/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:56:42 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/11 18:10:20 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

void	exit_thread(int exit_code)
{
	g_live_tm = -1;
	g_run = false;
	exit(exit_code);
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
	while (true)
	{
		print(phl_numb + 1, "is thinking", g_live);
		lock_fork(phl_numb);
		print(phl_numb + 1, "is eating", g_live);
		++phl_eated;
		g_live_tm = get_time();
		ft_sleep(g_phl_cfg.tm_to_eat);
		sem_post(g_forks);
		if (phl_eated >= g_phl_cfg.each_must_eat && g_phl_cfg.each_must_eat > 0)
			exit_thread(EX_FULL);
		print(phl_numb + 1, "is sleeping", g_live);
		ft_sleep(g_phl_cfg.tm_to_sleep);
	}
	exit_thread(EX_UNDEFINDED);
}

void	clear_threads(void)
{
	int i;
	int stt;

	g_live = false;
	waitpid(-1, &stt, WUNTRACED);
	stt = stt >> 8;
	i = 0;
	if (stt == EX_FULL)
	{
		while (++i < g_phl_cfg.nbr_of_philos)
		{
			waitpid(-1, &stt, WUNTRACED);
			if (stt == 1)
				while (++i < g_phl_cfg.nbr_of_philos)
					kill(g_philo[i], 0);
		}
	}
	else
		while (++i < g_phl_cfg.nbr_of_philos)
			kill(g_philo[i], 0);
	sem_close(g_forks);
	sem_close(g_print_lock);
	sem_unlink("print");
	sem_unlink("forks");
}

void	*check_death(void *i_addr)
{
	const	int i = (int)i_addr;

	while (true)
	{
		if (get_time() - g_live_tm > g_phl_cfg.tm_to_die)
		{
			print(i + 1, "died", false);
			exit(1);
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

void	thread_init(void)
{
	int		i;

	g_start_time = get_time() + 1000;
	g_live = true;
	sem_unlink("print");
	sem_unlink("forks");
	g_forks = sem_open("forks", O_CREAT, 0644, g_phl_cfg.nbr_of_philos / 2);
	g_print_lock = sem_open("print", O_CREAT, 0644, 1);
	i = 0;
	while (i < g_phl_cfg.nbr_of_philos)
	{
		g_philo[i] = fork();
		if (g_philo[i] == 0)
			philo_life((void*)(long)i);
		i++;
	}
	clear_threads();
}
