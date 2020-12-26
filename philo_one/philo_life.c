/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:56:42 by jiandre           #+#    #+#             */
/*   Updated: 2020/12/26 17:25:06 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void	ft_sleep(int time)
{
	int		i;

	i = 0;
	while (i++ < time * 10)
		usleep(100);
}

void	*philo(void *data)
{
	const int	i = (int)data;
	int			l_fork;
	int			r_fork;

	l_fork = i % phl_cfg.nbr_of_philos;
	r_fork = (i + 1) % phl_cfg.nbr_of_philos;
	while (true)
	{
		print("philo", i + 1, "thinking");
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
		ft_sleep(phl_cfg.tm_to_eat);
		print("philo", i + 1, "eating");
		pthread_mutex_unlock(&forks[l_fork]);
		pthread_mutex_unlock(&forks[r_fork]);
		print("philo", i + 1, "sleeping");
		ft_sleep(phl_cfg.tm_to_sleep);
	}
	return (0);
}

void	thread_init(struct philo_data *phl_cfg)
{
	int	i;

	philos = malloc(sizeof(pthread_t) * phl_cfg->nbr_of_philos);
	forks = malloc(sizeof(pthread_mutex_t) * phl_cfg->nbr_of_philos);
	start_time = get_time();
	i = 0;
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
	pthread_join(philos[i - 1], NULL);
}