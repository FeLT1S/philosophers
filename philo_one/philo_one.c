/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:02:15 by jiandre           #+#    #+#             */
/*   Updated: 2020/12/15 21:33:50 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo_one.h"
#include <stdbool.h>
#include <unistd.h>

int		init_data(int ac, char **av, struct philo_data *phl_cfg)
{
	if ((phl_cfg->nbr_of_philos = ft_atoi(av[1])) < 1)
		return (1);
	if ((phl_cfg->tm_to_die = ft_atoi(av[2])) < 1)
		return (1);
	if ((phl_cfg->tm_to_eat = ft_atoi(av[3])) < 1)
		return (1);
	if ((phl_cfg->tm_to_sleep = ft_atoi(av[4])) < 1)
		return (1);
	if (ac == 6 && (phl_cfg->each_must_eat = ft_atoi(av[5])) < 1)
		return (1);
	return (0);
}

void	*philo(void *phl_stt_addr)
{
	const struct philo_stat *phl_stt = phl_stt_addr;
	const struct philo_data *phl_cfg = phl_stt->phl_cfg;
	t_forks		forks;

	forks = *(phl_stt->forks);
	while (true)
	{
		print("philo", phl_stt->phl_nbr, "dream");
		pthread_mutex_lock(&forks[(phl_stt->phl_nbr % phl_cfg->nbr_of_philos)]);
		pthread_mutex_lock(&forks[(phl_stt->phl_nbr + 1) % phl_cfg->nbr_of_philos]);
		print("philo", phl_stt->phl_nbr, "eat");
		usleep(phl_cfg->tm_to_eat * 1000);
		pthread_mutex_unlock(&forks[(phl_stt->phl_nbr % phl_cfg->nbr_of_philos)]);
		pthread_mutex_unlock(&forks[(phl_stt->phl_nbr + 1) % phl_cfg->nbr_of_philos]);
		print("philo", phl_stt->phl_nbr, "sleep");
		usleep(phl_cfg->tm_to_sleep * 1000);
	}
}

void	thread_init(struct philo_data *phl_cfg)
{
	t_philos			philos;
	t_forks				forks;
	int					i;
	struct philo_stat	*phl_stt;
	struct timeval		old;

	i = 0;
	philos = malloc(sizeof(pthread_t) * phl_cfg->nbr_of_philos);
	forks = malloc(sizeof(pthread_mutex_t) * phl_cfg->nbr_of_philos);
	phl_stt = malloc(sizeof(struct philo_stat) * phl_cfg->nbr_of_philos);
	while (i < phl_cfg->nbr_of_philos)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < phl_cfg->nbr_of_philos)
	{
		phl_stt[i].phl_nbr = i + 1;
		phl_stt[i].forks = &forks;
		phl_stt[i].phl_cfg = phl_cfg;
		phl_stt[i].tm_alive = get_time();
		phl_stt[i].tm_alive = old.tv_usec;
		pthread_create(&philos[i], NULL, philo, &phl_stt[i]);
		usleep(50);
		i++;
	}
	pthread_join(philos[i - 1], NULL);
}

int		main(int ac, char *av[])
{
	struct philo_data	phl_cfg;

	pthread_mutex_init(&print_mutex, NULL);
	if (ac < 5 || ac > 6)
		print("Too many or low arguments", 0, NULL);
	else if ((init_data(ac, av, &phl_cfg)))
		print("Arguments not right", 0, NULL);
	else
		thread_init(&phl_cfg);
	return(0);
}