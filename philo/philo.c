/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:03:57 by zait-bel          #+#    #+#             */
/*   Updated: 2024/08/17 13:59:27 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(char *str, pthread_mutex_t *mutex, t_infos *pi, long long time)
{
	pthread_mutex_lock(mutex);
	printf("%lld %d %s", time, pi->philo_num, str);
	pthread_mutex_lock(&pi->arg->die_lock);
	if (pi->die_flag == 0)
		pthread_mutex_unlock(mutex);
	pthread_mutex_unlock(&pi->arg->die_lock);
}

void	*threadfunction(void *arg)
{
	t_infos			*pi;

	pi = (t_infos *)arg;
	if (pi->philo_num % 2 == 0)
		ft_usleep(pi->arg->eat_time / 2);
	while (pi->num_eat_time)
	{
		pthread_mutex_lock(pi->right_fork);
		print("has taken a fork\n", &pi->arg->print, pi, ft_time() - pi->time);
		pthread_mutex_lock(pi->left_fork);
		print("has taken a fork\n", &pi->arg->print, pi, ft_time() - pi->time);
		(pthread_mutex_lock(&pi->arg->eat_lock), pi->eat_last = ft_time());
		if (pi->num_eat_time > 0)
			pi->num_eat_time--;
		pthread_mutex_unlock(&pi->arg->eat_lock);
		print("is eating\n", &pi->arg->print, pi, ft_time() - pi->time);
		(ft_usleep(pi->arg->eat_time), pthread_mutex_unlock(pi->left_fork));
		pthread_mutex_unlock(pi->right_fork);
		print("is sleeping\n", &pi->arg->print, pi, ft_time() - pi->time);
		ft_usleep(pi->arg->sleep_time);
		print("is thinking\n", &pi->arg->print, pi, ft_time() - pi->time);
	}
	return (NULL);
}

void	monitoring(t_infos *pi)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < pi->arg->num_of_philo)
		{
			pthread_mutex_lock(&pi->arg->eat_lock);
			if (ft_time() - pi[i].eat_last >= pi->arg->die_time)
			{
				pthread_mutex_unlock(&pi->arg->eat_lock);
				pthread_mutex_lock(&pi->arg->die_lock);
				pi[i].die_flag = 1;
				pthread_mutex_unlock(&pi->arg->die_lock);
				if (pi->num_eat_time)
					print("died\n", &pi->arg->print, &pi[i],
						ft_time() - pi->time);
				return ;
			}
			pthread_mutex_unlock(&pi->arg->eat_lock);
			i++;
		}
		usleep(500);
	}
}

void	philo(t_arg *p)
{
	t_infos		*pi;
	int			i;
	pthread_t	*threads;

	pi = malloc(sizeof(t_infos) * p->num_of_philo);
	if (!pi)
		return ;
	threads = malloc(sizeof(pthread_t) * p->num_of_philo);
	if (!threads)
		return (free(pi));
	pi->arg = p;
	pi->arg->fork_mutex = malloc(sizeof(pthread_mutex_t) * p->num_of_philo);
	if (!pi->arg->fork_mutex)
		return (free(pi), free(threads));
	if (init_mutex(p, pi))
		return (free(pi), free (threads), free(pi->arg->fork_mutex));
	i = -1;
	while (++i < p->num_of_philo)
		if (pthread_create(&threads[i], NULL, threadfunction, &pi[i]))
			return (destroy_free(p, pi, threads));
	i = -1;
	while (++i < p->num_of_philo)
		if (pthread_detach(threads[i]))
			return (destroy_free(p, pi, threads));
	(monitoring(pi), destroy_free(p, pi, threads));
}

int	main(int argc, char **argv)
{
	t_arg	*p;

	p = NULL;
	if (argc == 5 || argc == 6)
	{
		p = malloc(sizeof(t_arg));
		if (!p)
			return (1);
		1 && (p->num_of_philo = f_atoi(argv[1]), p->die_time = f_atoi(argv[2]));
		1 && (p->eat_time = f_atoi(argv[3]), p->sleep_time = f_atoi(argv[4]));
		if (argc == 6)
		{
			p->num_eat_time = f_atoi(argv[5]);
			if (p->num_eat_time < 0)
				return (write(2, "Error in input\n", 16), 1);
		}
		else
			p->num_eat_time = -1;
		if (p->num_of_philo <= 0 || p->die_time <= 0
			|| p->eat_time <= 0 || p->sleep_time <= 0)
			return (write(2, "Error in input\n", 16), 1);
		(philo(p), free(p));
	}
	else
		write(2, "Error in input\n", 16);
}
