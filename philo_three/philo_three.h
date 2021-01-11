/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:44:13 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/11 18:09:41 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include "string.h"
# include <pthread.h>
# include <stdbool.h>
# include <semaphore.h>

# define MAX_PHLS 200

typedef pthread_t			t_philos;

pid_t						g_philo[MAX_PHLS];
sem_t						*g_forks;
sem_t						*g_print_lock;
long						g_start_time;
bool						g_live;
int							g_live_tm;
bool						g_run;

struct						s_philo_data
{
	int						nbr_of_philos;
	int						tm_to_die;
	int						tm_to_eat;
	int						tm_to_sleep;
	int						each_must_eat;
};

enum	e_exit_code{
	EX_UNDEFINDED,
	EX_DIED,
	EX_FULL
};

struct s_philo_data			g_phl_cfg;

void						print(int nbr, char *str2, bool live);
int							ft_atoi(char *str_nbr);
void						ft_putnbr_fd(long n);
int							get_time(void);
void						thread_init(void);
void						lock_fork(const int i);
void						ft_sleep(int time);
void						sleep_untill(int ms_stamp);
void						*check_death(void *i_addr);

#endif
