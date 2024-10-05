/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:52:07 by zait-bel          #+#    #+#             */
/*   Updated: 2024/08/17 14:08:26 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	f_atoi(const char *str)
{
	int		i;
	int		s;
	size_t	r;

	1 && (i = 0, s = 1, r = 0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			s = -1;
	if (!str[i])
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + str[i++] - 48;
		if ((r >= __LONG_MAX__) && s == 1)
			return (-1);
		else if ((r > __LONG_MAX__) && s == -1)
			return (-1);
	}
	if (str[i])
		return (-1);
	return (r * s);
}

int	init_mutex(t_arg *p, t_infos *pi)
{
	int	i;

	i = -1;
	while (++i < p->num_of_philo)
		if (pthread_mutex_init(&pi->arg->fork_mutex[i], NULL))
			return (printf("error in mutex_init\n"));
	if (pthread_mutex_init(&pi->arg->eat_lock, NULL))
		return (printf("error in mutex_init\n"));
	if (pthread_mutex_init(&pi->arg->print, NULL))
		return (printf("error in mutex_init\n"));
	if (pthread_mutex_init(&pi->arg->die_lock, NULL))
		return (printf("error in mutex_init\n"));
	init_data(p, pi);
	return (0);
}

void	init_data(t_arg *p, t_infos *pi)
{
	int			i;
	long long	time;

	time = ft_time();
	i = 0;
	while (i < p->num_of_philo)
	{
		pi[i].die_flag = 0;
		pi[i].time = time;
		pi[i].eat_last = time;
		pi[i].arg = p;
		pi[i].num_eat_time = p->num_eat_time;
		pi[i].philo_num = i + 1;
		pi[i].right_fork = &p->fork_mutex[i];
		pi[i].left_fork = &p->fork_mutex[(i + 1) % p->num_of_philo];
		i++;
	}
}

void	destroy_free(t_arg *p, t_infos *pi, pthread_t *threads)
{
	int	i;

	i = -1;
	ft_usleep(50);
	while (++i < p->num_of_philo)
		pthread_mutex_destroy(pi->arg->fork_mutex);
	pthread_mutex_destroy(&pi->arg->print);
	pthread_mutex_destroy(&pi->arg->eat_lock);
	pthread_mutex_destroy(&pi->arg->die_lock);
	(free(pi->arg->fork_mutex), free(threads), free(pi));
}
