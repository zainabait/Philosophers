/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:35:35 by zait-bel          #+#    #+#             */
/*   Updated: 2024/08/16 00:16:17 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print(char *str, sem_t *sem, t_infos *pi, long long time)
{
	sem_wait(sem);
	printf("%lld %d %s", time, pi->philo_num, str);
	if (str[0] != 'd')
		sem_post(sem);
}

void	processfunction(t_infos *pi)
{
	while (pi->num_eat_time)
	{
		sem_wait(pi->arg->fork_sem);
		print("has taken a fork\n", pi->arg->print, pi,
			ft_time() - pi->arg->time);
		sem_wait(pi->arg->fork_sem);
		print("has taken a fork\n", pi->arg->print, pi,
			ft_time() - pi->arg->time);
		pi->eat_last = ft_time();
		if (pi->num_eat_time > 0)
			pi->num_eat_time--;
		print("is eating\n", pi->arg->print, pi, ft_time() - pi->arg->time);
		(ft_usleep(pi->arg->eat_time), sem_post(pi->arg->fork_sem));
		sem_post(pi->arg->fork_sem);
		print("is sleeping\n", pi->arg->print, pi, ft_time() - pi->arg->time);
		ft_usleep(pi->arg->sleep_time);
		print("is thinking\n", pi->arg->print, pi, ft_time() - pi->arg->time);
	}
	exit(19);
}

void	*monitoring(void *arg)
{
	t_infos	*pi;

	pi = (t_infos *)arg;
	while (1)
	{
		if (ft_time() - pi->eat_last >= pi->arg->die_time)
		{
			if (pi->num_eat_time)
				print("died\n", pi->arg->print, pi,
					ft_time() - pi->arg->time);
			exit(18);
		}
	}
}

void	philo(t_arg *p)
{
	t_infos		*pi;
	int			i;
	pthread_t	threads;

	pi = malloc(sizeof(t_infos) * p->num_of_philo);
	if (!pi)
		return ;
	if (init_data(p, pi))
		return (free(pi));
	1 && (i = -1, p->time = ft_time());
	while (++i < p->num_of_philo)
	{
		pi[i].pid = fork();
		if (pi[i].pid == -1)
			(kill_fail(pi, i), free(pi), exit(1));
		if (pi[i].pid == 0)
		{
			pi[i].eat_last = p->time;
			if (pthread_create(&threads, NULL, monitoring, &pi[i])
				|| pthread_detach(threads))
				return (kill_fail(pi, i), printf("Error\n"), destroy_free(pi));
			processfunction(&pi[i]);
		}
	}
	(ft_kill(pi), destroy_free(pi));
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
