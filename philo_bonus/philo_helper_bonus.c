/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:35:43 by zait-bel          #+#    #+#             */
/*   Updated: 2024/08/17 14:11:06 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

long long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long long time)
{
	long long	new;

	new = ft_time();
	while (ft_time() - new < time)
		usleep(500);
}

int	init_data(t_arg *p, t_infos *pi)
{
	int	i;

	sem_unlink("/forksemaphore");
	sem_unlink("/printsemaphore");
	p->fork_sem = sem_open("/forksemaphore", O_CREAT | O_EXCL,
			0644, p->num_of_philo);
	if (p->fork_sem == SEM_FAILED)
		return (printf("Error with sem_open\n"));
	p->print = sem_open("/printsemaphore", O_CREAT | O_EXCL, 0644, 1);
	if (p->print == SEM_FAILED)
		return (printf("Error with sem_open\n"));
	i = 0;
	while (i < p->num_of_philo)
	{
		pi[i].arg = p;
		pi[i].num_eat_time = p->num_eat_time;
		pi[i].philo_num = i + 1;
		i++;
	}
	return (0);
}

void	destroy_free(t_infos *pi)
{
	if (pi)
	{
		sem_close(pi->arg->fork_sem);
		sem_close(pi->arg->print);
		sem_unlink("/forksemaphore");
		sem_unlink("/printsemaphore");
		free(pi);
	}
}
