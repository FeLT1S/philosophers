/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:44:13 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/03 16:19:52 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include "string.h"
#include <pthread.h>
#include <stdbool.h>

typedef		pthread_t		*t_philos;
typedef		pthread_mutex_t	*t_fork_st;

pthread_mutex_t				print_mutex;
t_philos					philos;
t_fork_st					fork_st;
long						start_time;
bool						live;
bool						*forks;

struct						philo_data
{
	int						nbr_of_philos;
	int						tm_to_die;
	int						tm_to_eat;
	int						tm_to_sleep;
	int						each_must_eat;
};

struct philo_data	phl_cfg;

size_t						ft_strlen(const char *s);
void						print(int nbr, char *str2, bool live);
int							ft_atoi(char *str_nbr);
void						ft_putnbr_fd(long n);
int							get_time(void);
void						thread_init(struct philo_data *phl_cfg);

#endif
