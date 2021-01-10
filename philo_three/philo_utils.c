/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:12:12 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/10 18:37:15 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include "philo_three.h"

int					get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

void				sleep_untill(int ms_stamp)
{
	while (true)
	{
		if (get_time() >= ms_stamp)
			return ;
		usleep(100);
	}
}

void				ft_sleep(int time)
{
	const long start = get_time();

	while (get_time() - start < time)
		usleep(100);
}

int					ft_atoi(char *str_nbr)
{
	int nbr;

	nbr = 0;
	while (*str_nbr)
	{
		if (*str_nbr < '0' || *str_nbr > '9')
			return (-1);
		nbr = (nbr * 10) + (*str_nbr - '0');
		str_nbr++;
		if (nbr < 0)
			return (-1);
	}
	return (nbr);
}
