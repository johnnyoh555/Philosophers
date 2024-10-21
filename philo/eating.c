/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:42:59 by jooh              #+#    #+#             */
/*   Updated: 2023/12/17 14:34:10 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	time_to_eat_l(t_info *info, t_philo *philo)
{
	while (check_dead(info, philo) == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		if (*(philo->real_l_fork) == 0)
		{
			*(philo->real_l_fork) = 1;
			ft_printf(info, philo, "has taken a fork", 4);
			pthread_mutex_unlock(philo->l_fork);
			return (0);
		}
		pthread_mutex_unlock(philo->l_fork);
		usleep(200);
	}
	return (1);
}

static int	time_to_eat_r(t_info *info, t_philo *philo)
{
	while (check_dead(info, philo) == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		if (*(philo->real_r_fork) == 0)
		{
			*(philo->real_r_fork) = 1;
			ft_printf(info, philo, "has taken a fork", 4);
			pthread_mutex_unlock(philo->r_fork);
			return (0);
		}
		pthread_mutex_unlock(philo->r_fork);
		usleep(200);
	}
	return (1);
}

void	right_handed(t_info *info, t_philo *philo)
{
	if (time_to_eat_r(info, philo))
		return ;
	if (time_to_eat_l(info, philo))
		return ;
	ft_printf(info, philo, "is eating", 0);
	time_go(info, philo, info->eat_time, 1);
	pthread_mutex_lock(philo->l_fork);
	*(philo->real_l_fork) = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	*(philo->real_r_fork) = 0;
	pthread_mutex_unlock(philo->r_fork);
}
