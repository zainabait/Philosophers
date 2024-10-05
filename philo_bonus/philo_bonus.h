/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:22:36 by zait-bel          #+#    #+#             */
/*   Updated: 2024/08/15 21:18:45 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H 

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct philo_arg
{
	int			num_of_philo;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			num_eat_time;
	long long	time;
	sem_t		*fork_sem;
	sem_t		*print;
}	t_arg;

typedef struct philo_infos
{
	int				philo_num;
	pid_t			pid;
	long long		eat_last;
	int				num_eat_time;
	t_arg			*arg;
}	t_infos;

long long	ft_time(void);
int			f_atoi(const char *str);
void		ft_usleep(long long time);
int			init_data(t_arg *p, t_infos *pi);
void		destroy_free(t_infos *pi);
void		ft_kill(t_infos *pi);
void		ft_kill_all(t_infos *pi);
void		kill_fail(t_infos *pi, int n);

#endif