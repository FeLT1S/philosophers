/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:44:13 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/11 18:13:59 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include "string.h"
# include <pthread.h>
# include <stdbool.h>
# include <semaphore.h>

# define MAX_PHLS 200

typedef pthread_t			t_philos;

sem_t						*g_forks;
sem_t						*g_print_lock;
long						g_start_time;
bool						g_live;
int							g_live_tm[MAX_PHLS];
bool						g_run[MAX_PHLS];

struct						s_philo_data
{
	int						nbr_of_philos;
	int						tm_to_die;
	int						tm_to_eat;
	int						tm_to_sleep;
	int						each_must_eat;
};

struct s_philo_data			g_phl_cfg;

void						print(int nbr, char *str2, bool live);
int							ft_atoi(char *str_nbr);
void						ft_putnbr_fd(long n);
int							get_time(void);
void						thread_init(void);
void						lock_fork(const int i);
void						check_die(int live_tm, int i);
void						ft_sleep(int time);
void						sleep_untill(int ms_stamp);

#endif
