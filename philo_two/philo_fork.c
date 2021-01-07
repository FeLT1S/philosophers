/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:40:55 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/08 21:01:06 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo_two.h"

void	lock_fork(const int i)
{
	sem_wait(g_forks);
	print(i + 1, "has taken a fork", g_live);
	print(i + 1, "has taken a fork", g_live);
}