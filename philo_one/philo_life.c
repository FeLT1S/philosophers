/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:56:42 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/03 19:34:40 by jiandre          ###   ########.fr       */
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

void	lock_fork(const int l_fork, const int r_fork, const int i, int live_tm)
{
	bool	l_taken;
	bool	r_taken;

	l_taken = false;
	r_taken = false;
	while (live)
	{
		if (!l_taken)
		{
			pthread_mutex_lock(&fork_st[l_fork]);
			if (!(forks[l_fork]))
			{
				forks[l_fork] = true;
				l_taken = true;
				print(i + 1, "has taken a fork", true);
			}
			pthread_mutex_unlock(&fork_st[l_fork]);
		}
		if (!r_taken)
		{
			pthread_mutex_lock(&fork_st[r_fork]);
			if (!(forks[r_fork]))
			{
				forks[r_fork] = true;
				r_taken = true;
				print(i + 1, "has taken a fork", true);
			}
			pthread_mutex_unlock(&fork_st[r_fork]);
		}
		if (l_taken && r_taken)
			break;
		if (get_time() - live_tm >= phl_cfg.tm_to_die)
			print(i + 1, "died", live = false);
	}
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
		if (get_time() - phl_live_tm >= phl_cfg.tm_to_die)
		{
			print(i + 1, "died", live = false);
			break;
		}
		if (l_fork < r_fork)
			lock_fork(l_fork, r_fork, i, phl_live_tm);
		else
			lock_fork(r_fork, l_fork, i, phl_live_tm);
		if (get_time() - phl_live_tm >= phl_cfg.tm_to_die)
		{
			print(i + 1, "died", live = false);
			break;
		}
		print(i + 1, "is eating", true);
		phl_live_tm = get_time();
		ft_sleep(phl_cfg.tm_to_eat, phl_live_tm);
		if (get_time() - phl_live_tm >= phl_cfg.tm_to_die)
		{
			print(i + 1, "died", live = false);
			break;
		}
		pthread_mutex_lock(&fork_st[l_fork]);
		forks[l_fork] = false;
		pthread_mutex_unlock(&fork_st[l_fork]);
		pthread_mutex_lock(&fork_st[r_fork]);
		forks[r_fork] = false;
		pthread_mutex_unlock(&fork_st[r_fork]);
		print(i + 1, "is sleeping", true);
		ft_sleep(phl_cfg.tm_to_sleep, phl_live_tm);
		if (get_time() - phl_live_tm >= phl_cfg.tm_to_die)
		{
			print(i + 1, "died", live = false);
			break;
		}
	}
	return (NULL);
}

void	thread_init(struct philo_data *phl_cfg)
{
	int		i;

	philos = malloc(sizeof(pthread_t) * phl_cfg->nbr_of_philos);
	fork_st = malloc(sizeof(pthread_mutex_t) * phl_cfg->nbr_of_philos);
	forks = malloc(sizeof(bool) * phl_cfg->nbr_of_philos);
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
		i++;
	}
	while (live)
		;
}