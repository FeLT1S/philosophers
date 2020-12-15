/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:44:13 by jiandre           #+#    #+#             */
/*   Updated: 2020/12/15 21:31:24 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include "string.h"
#include <pthread.h>

pthread_mutex_t	print_mutex;

typedef		pthread_t		*t_philos;
typedef		pthread_mutex_t	*t_forks;

struct		philo_data
{
	int		nbr_of_philos;
	int		tm_to_die;
	int		tm_to_eat;
	int		tm_to_sleep;
	int		each_must_eat;
};

struct		philo_stat
{
	int					phl_nbr;
	t_forks				*forks;
	struct philo_data	*phl_cfg;
	int					tm_alive;
};

size_t			ft_strlen(const char *s);
void			print(char *str, int nbr, char *str2);
int				ft_atoi(char *str_nbr);
void			ft_putnbr_fd(long n, int fd);
int				get_time(void);

#endif
