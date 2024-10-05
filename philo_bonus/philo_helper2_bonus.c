/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:24:13 by zait-bel          #+#    #+#             */
/*   Updated: 2024/08/17 14:12:54 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_kill_all(t_infos *pi)
{
	int	i;

	i = -1;
	while (++i < pi->arg->num_of_philo)
		kill(pi[i].pid, SIGTERM);
}

void	kill_fail(t_infos *pi, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		kill(pi[i].pid, SIGTERM);
}

void	ft_kill(t_infos *pi)
{
	int	status;
	int	i;

	i = -1;
	while (++i < pi->arg->num_of_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 18)
		{
			ft_kill_all(pi);
			break ;
		}
	}
}
