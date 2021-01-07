/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:40:55 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/07 21:20:45 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo_one.h"

void	lock_fork(const int l_fork, const int r_fork, const int i)
{
	pthread_mutex_lock(&g_fork[l_fork]);
	print(i + 1, "has taken a fork", true);
	pthread_mutex_lock(&g_fork[r_fork]);
	print(i + 1, "has taken a fork", true);
}

void	unlock_fork(const int l_fork, const int r_fork)
{
	pthread_mutex_unlock(&g_fork[l_fork]);
	pthread_mutex_unlock(&g_fork[r_fork]);
}

int		take_lfork(int i)
{
	if (i % g_phl_cfg.nbr_of_philos < (i + 1) % g_phl_cfg.nbr_of_philos)
		return (i % g_phl_cfg.nbr_of_philos);
	else
		return ((i + 1) % g_phl_cfg.nbr_of_philos);
}

int		take_rfork(int i)
{
	if (i % g_phl_cfg.nbr_of_philos < (i + 1) % g_phl_cfg.nbr_of_philos)
		return ((i + 1) % g_phl_cfg.nbr_of_philos);
	else
		return (i % g_phl_cfg.nbr_of_philos);
}
