/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:56:42 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/02 22:08:00 by jiandre          ###   ########.fr       */
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
		usleep(100);
}

void	lock_fork(const int l_fork, const int r_fork)
{
	if (l_fork > r_fork)
	{
		pthread_mutex_lock(&forks[r_fork]);
		pthread_mutex_lock(&forks[l_fork]);
	}
	else
	{
		pthread_mutex_lock(&forks[l_fork]);
		pthread_mutex_lock(&forks[r_fork]);
	}
}

bool	phl_dstr(int numb)
{
	int i;

	i = 0;
	print(numb + 1, "died");
	return (false);
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
		print(i + 1, "is thinking");
		if (get_time() - phl_live_tm >= phl_cfg.tm_to_die)
		{
			phl_dstr(i);
			live = false;
			break;
		}
		lock_fork(l_fork, r_fork);
		if (get_time() - phl_live_tm >= phl_cfg.tm_to_die)
		{
			phl_dstr(i);
			live = false;
			break;
		}	
		print(i + 1, "has taken a fork");
		phl_live_tm = get_time();
		print(i + 1, "is eating");
		ft_sleep(phl_cfg.tm_to_eat, phl_live_tm);
		if (get_time() - phl_live_tm >= phl_cfg.tm_to_die)
		{
			phl_dstr(i);
			live = false;
			break;
		}
		pthread_mutex_unlock(&forks[l_fork]);
		pthread_mutex_unlock(&forks[r_fork]);
		print(i + 1, "is sleeping");
		ft_sleep(phl_cfg.tm_to_sleep, phl_live_tm);
		if (get_time() - phl_live_tm >= phl_cfg.tm_to_die)
		{
			phl_dstr(i);
			live = false;
			break;
		}
	}
	return (NULL);
}

void	thread_init(struct philo_data *phl_cfg)
{
	int		i;

	philos = malloc(sizeof(pthread_t) * phl_cfg->nbr_of_philos);
	forks = malloc(sizeof(pthread_mutex_t) * phl_cfg->nbr_of_philos);
	start_time = get_time();
	i = 0;
	live = true;
	while(i < phl_cfg->nbr_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while(i < phl_cfg->nbr_of_philos)
	{
		pthread_create(&philos[i], NULL, philo, (void*)(long)i);
		i++;
	}
	while (live)
		;
}