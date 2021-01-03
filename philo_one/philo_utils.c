/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:12:12 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/03 16:20:06 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include "philo_one.h"

size_t			ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int					get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

void				ft_putnbr_fd(long n)
{
	char			symb;
	unsigned long	m;

	if (n < 0)
	{
		write(STDOUT_FILENO, "-", 1);
		n = -n;
	}
	m = (unsigned long)n;
	if (m >= 10)
	{
		ft_putnbr_fd(m / 10);
		symb = (m % 10) + '0';
		write(STDOUT_FILENO, &symb, 1);
	}
	if (m >= 0 && m <= 9)
	{
		symb = m + '0';
		write(STDOUT_FILENO, &symb, 1);
	}
}

void	print(int nbr, char *str2, bool stt)
{
	pthread_mutex_lock(&print_mutex);
	ft_putnbr_fd(get_time() - start_time);
	if (nbr)
	{
		write(1, " ", 1);
		ft_putnbr_fd(nbr);
		write(1, " ", 1);
		write(1, str2, ft_strlen(str2));
	}
	write(1, "\n", 1);
	if (stt)
		pthread_mutex_unlock(&print_mutex);
}

int		ft_atoi(char *str_nbr)
{
	int nbr;

	nbr = 0;
	while(*str_nbr)
	{
		if (*str_nbr < '0' || *str_nbr > '9')
			return (-1);
		nbr = (nbr * 10) + (*str_nbr - '0');
		str_nbr++;
	}
	return (nbr);
}
