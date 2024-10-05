/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:21:34 by zait-bel          #+#    #+#             */
/*   Updated: 2024/08/17 15:20:10 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct philo_arg
{
	int					num_of_philo;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					num_eat_time;
	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		eat_lock;
	pthread_mutex_t		print;
	pthread_mutex_t		die_lock;
}	t_arg;

typedef struct philo_infos
{
	int					philo_num;
	long long			time;
	long long			eat_last;
	int					die_flag;
	int					num_eat_time;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	t_arg				*arg;
}	t_infos;

int			f_atoi(const char *str);
void		ft_usleep(long long time);
long long	ft_time(void);
void		init_data(t_arg *p, t_infos *pi);
void		destroy_free(t_arg *p, t_infos *pi, pthread_t *threads);
int			init_mutex(t_arg *p, t_infos *pi);

#endif