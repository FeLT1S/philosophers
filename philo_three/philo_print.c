/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:36:58 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/10 18:37:06 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo_three.h"

static void				*ft_memcpy(void *dst, const void *src, size_t n)
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

static size_t			ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int				ft_itoa_len(int n)
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

static int				ft_itoa(long n, char *str)
{
	int		len;
	int		len2;
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

void					print(int nbr, char *str2, bool stt)
{
	char	buff[500];
	int		i;
	int		len;

	if (stt == false)
		return ;
	i = 0;
	memset(buff, 0, 500);
	sem_wait(g_print_lock);
	i += ft_itoa(get_time() - g_start_time, buff + i);
	if (nbr)
	{
		buff[i++] = ' ';
		i += ft_itoa(nbr, buff + i);
		buff[i++] = ' ';
		len = ft_strlen(str2);
		ft_memcpy(buff + i, str2, len);
		i += len;
		buff[i++] = '\n';
	}
	write(1, buff, ft_strlen(buff));
	sem_post(g_print_lock);
}
