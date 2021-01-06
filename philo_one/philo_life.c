/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:56:42 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/06 21:00:27 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void	ft_sleep(int time, int phl_live_tm)
{
	const long start = get_time();

	if (time > phl_cfg.tm_to_die - get_time() + phl_live_tm)
		time = phl_cfg.tm_to_die - get_time() + phl_live_tm;
	while (get_time() - start < time)
		usleep(50);
}

void	check_die(int live_tm, int i)
{
	if (get_time() - live_tm > phl_cfg.tm_to_die)
	{
		print(i + 1, "died", false);
		live = false;
	}
}

void	lock_fork(const int l_fork, const int r_fork, const int i, int live_tm)
{
	while (forks[l_fork] && live)
	{
		check_die(live_tm, i);
		usleep(50);
	}
	pthread_mutex_lock(&fork_st[l_fork]);
	forks[l_fork] = true;
	print(i + 1, "has taken a fork", true);
	pthread_mutex_unlock(&fork_st[l_fork]);
	while (forks[r_fork] && live)
	{
		check_die(live_tm, i);
		usleep(50);
	}
	pthread_mutex_lock(&fork_st[r_fork]);
	forks[r_fork] = true;
	print(i + 1, "has taken a fork", true);
	pthread_mutex_unlock(&fork_st[r_fork]);
}

void	unlock_fork(const int l_fork, const int r_fork)
{
		pthread_mutex_lock(&fork_st[r_fork]);
		forks[r_fork] = false;
		pthread_mutex_unlock(&fork_st[r_fork]);
		pthread_mutex_lock(&fork_st[l_fork]);
		forks[l_fork] = false;
		pthread_mutex_unlock(&fork_st[l_fork]);
}


void	*philo(void *data)
{
	const int	i = (int)data;
	const int	l_fork = i % phl_cfg.nbr_of_philos;
	const int	r_fork = (i + 1) % phl_cfg.nbr_of_philos;
	int			phl_live_tm;

	phl_live_tm = get_time();
	while (live)
	{
		print(i + 1, "is thinking", true);
		if (l_fork < r_fork)
			lock_fork(l_fork, r_fork, i, phl_live_tm);
		else
			lock_fork(r_fork, l_fork, i, phl_live_tm);
		check_die(phl_live_tm, i);
		print(i + 1, "is eating", true);
		phl_live_tm = get_time();
		ft_sleep(phl_cfg.tm_to_eat, phl_live_tm);
		unlock_fork(l_fork, r_fork);
		check_die(phl_live_tm, i);
		print(i + 1, "is sleeping", true);
		ft_sleep(phl_cfg.tm_to_sleep, phl_live_tm);
		check_die(phl_live_tm, i);
	}
	return (NULL);
}

void	thread_init(struct philo_data *phl_cfg)
{
	int		i;

	memset(forks, 0, sizeof(bool) * phl_cfg->nbr_of_philos);
	start_time = get_time();
	i = 0;
	live = true;
	while(i < phl_cfg->nbr_of_philos)
	{
		pthread_mutex_init(&fork_st[i], NULL);
		i++;
	}
	i = 0;
	while(i < phl_cfg->nbr_of_philos)
	{
		pthread_create(&philos[i], NULL, philo, (void*)(long)i);
		pthread_detach(philos[i]);
		if (i % 2)
			usleep(200);
		i++;
	}
	while (live)
		;
}