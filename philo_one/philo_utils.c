/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:12:12 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/06 20:42:44 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include "philo_one.h"

void					*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long		*long_dst;
	const unsigned long	*long_src;
	unsigned char		*ch_dst;
	const unsigned char	*ch_src;
	unsigned long		i;

	if (!dst && !src)
		return (0);
	ch_dst = dst;
	ch_src = src;
	i = 0;
	while (i++ < n && ((unsigned long)dst & (sizeof(long) - 1)) != 0)
		*ch_dst++ = *ch_src++;
	long_dst = (unsigned long*)dst;
	long_src = (const unsigned long*)src;
	i = 0;
	while (i++ < (unsigned long)n / sizeof(long))
		*long_dst++ = *long_src++;
	ch_dst = (unsigned char*)long_dst;
	ch_src = (const unsigned char*)long_src;
	i = 0;
	while (i++ < (unsigned long)n % sizeof(long))
		*ch_dst++ = *ch_src++;
	return (dst);
}

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

void	print(int nbr, char *str2, bool stt)
{
	char	buff[500];
	int		i;
	int		len;

	i = 0;
	memset(buff, 0, 500);
	pthread_mutex_lock(&print_mutex);
	i += ft_itoa(get_time() - start_time, buff + i);
	if (nbr)
	{
		buff[i++] = ' ';
		i += ft_itoa(nbr, buff + i);
		buff[i++] = ' ';
		len = ft_strlen(str2);
		ft_memcpy(buff + i, str2, len);
		i +=len;
		buff[i++] = '\n';
	}
	write(1, buff, ft_strlen(buff));
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

static int	ft_itoa_len(int n)
{
	int		len;

	len = 0;
	while (n > 9 || n < -9)
	{
		len++;
		n /= 10;
	}
	len++;
	if (n < 0)
		len++;
	return (len);
}

int		ft_itoa(long n, char *str)
{
	int		len;
	int 	len2;
	long	m;

	m = (long)n;
	len = ft_itoa_len(n);
	len2 = len;
	m == 0 ? *str = '0' : 0;
	while (m != 0)
	{
		str[--len] = m % 10 + '0';
		m /= 10;
	}
	return (len2);
}