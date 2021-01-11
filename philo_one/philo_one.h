/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:44:13 by jiandre           #+#    #+#             */
/*   Updated: 2021/01/11 18:15:57 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include "string.h"
# include <pthread.h>
# include <stdbool.h>

# define MAX_PHLS 200

typedef pthread_t			t_philos;
typedef pthread_mutex_t		t_fork_st;

pthread_mutex_t				g_print_mutex;
t_fork_st					g_fork[MAX_PHLS];
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
int							take_lfork(int i);
int							take_rfork(int i);
void						lock_fork(const int l_fork, const int r_fork,
								const int i);
void						unlock_fork(const int l_fork, const int r_fork);
void						check_die(int live_tm, int i);
void						ft_sleep(int time);
void						sleep_untill(int ms_stamp);

#endif
