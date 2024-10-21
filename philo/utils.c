/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:13:34 by jooh              #+#    #+#             */
/*   Updated: 2023/12/10 14:20:59 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printf(t_info *info, t_philo *philo, char *str, int flag)
{
	int	id;

	id = philo->id + 1;
	pthread_mutex_lock(&(info->printer));
	if (flag != 1 && get_time() > philo->last_eat + info->die_time
		&& info->end_flag == 0)
	{
		printf("\e[31m%ld %d died\e[0m\n", get_time() - info->start, id);
		info->end_flag = 1;
	}
	else if (flag == 0 && info->end_flag == 0)
		printf("\e[32m%ld %d %s\e[0m\n", get_time() - info->start, id, str);
	else if (flag == 1 && info->end_flag == 0)
	{
		printf("\e[31m%ld %d %s\e[0m\n", get_time() - info->start, id, str);
		info->end_flag = 1;
	}
	else if (flag == 2 && info->end_flag == 0)
		printf("\e[33m%ld %d %s\e[0m\n", get_time() - info->start, id, str);
	else if (flag == 3 && info->end_flag == 0)
		printf("\e[34m%ld %d %s\e[0m\n", get_time() - info->start, id, str);
	else if (flag == 4 && info->end_flag == 0)
		printf("\e[35m%ld %d %s\e[0m\n", get_time() - info->start, id, str);
	pthread_mutex_unlock(&(info->printer));
}

int	check_end(t_info *info)
{
	pthread_mutex_lock(&info->printer);
	if (info->end_flag == 1)
	{
		pthread_mutex_unlock(&info->printer);
		return (1);
	}
	pthread_mutex_unlock(&info->printer);
	return (0);
}

int	check_dead(t_info *info, t_philo *philo)
{
	if (check_end(info))
		return (1);
	if (get_time() > philo->last_eat + info->die_time)
	{
		ft_printf(info, philo, "died", 1);
		return (1);
	}
	return (0);
}

int	err_seq(t_info *info, t_philo *philo, int i)
{
	char	*str;

	end_seq(info, philo);
	if (i == 1)
		str = "argument: wrong arguments";
	else if (i == 2)
		str = "mutex: fail to make mutex";
	else if (i == 3)
		str = "malloc: fail to allocate";
	else if (i == 4)
		str = "gettimeofday: fail to get time";
	else
		str = "thread: fail to create a thread";
	printf("\e[31mphilo: %s\e[0m\n", str);
	return (i);
}

void	end_seq(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	if (info->real_fork)
		free(info->real_fork);
	while (i < info->humans)
	{
		if (info->fork)
			pthread_mutex_destroy(&(info->fork[i]));
		if (philo && philo[i].thread)
			free(philo[i].thread);
		i++;
	}
	if (info->fork)
		free(info->fork);
	pthread_mutex_destroy(&(info->printer));
	pthread_mutex_destroy(&(info->startline));
	if (philo)
		free(philo);
}
