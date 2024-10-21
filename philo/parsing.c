/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:57:55 by jooh              #+#    #+#             */
/*   Updated: 2023/12/10 14:03:13 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_philos(t_info *info, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < info->humans)
	{
		philo[i].info = info;
		philo[i].eat = 0;
		philo[i].id = i;
		philo[i].l_fork = &(info->fork[i]);
		philo[i].r_fork = &(info->fork[(i + 1) % info->humans]);
		philo[i].real_l_fork = &(info->real_fork[i]);
		philo[i].real_r_fork = &(info->real_fork[(i + 1) % info->humans]);
		philo[i].thread = malloc(sizeof(pthread_t));
		if (philo[i].thread == 0)
			return (ALLOCERR);
		i++;
	}
	return (0);
}

int	make_forks(t_info *info)
{
	int	i;

	if (pthread_mutex_init(&(info->printer), 0) != 0)
		return (MUTEXERR);
	if (pthread_mutex_init(&(info->startline), 0) != 0)
		return (MUTEXERR);
	info->fork = malloc(sizeof(pthread_mutex_t) * info->humans);
	if (info->fork == 0)
		return (ALLOCERR);
	info->real_fork = malloc(sizeof(int) * info->humans);
	if (info->real_fork == 0)
		return (ALLOCERR);
	i = 0;
	while (i < info->humans)
	{
		if (pthread_mutex_init(&(info->fork)[i], 0) == -1)
			return (MUTEXERR);
		info->real_fork[i] = 0;
		i++;
	}
	return (0);
}

int	init_info(t_info *info, char *av[], int ac)
{
	info->humans = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->slp_time = ft_atoi(av[4]);
	info->start = get_time() + 100;
	info->max_eat = 0;
	info->end_flag = 0;
	if (info->humans <= 0 || info->die_time <= 0 || info->eat_time <= 0
		|| info->slp_time <= 0)
		return (ARGERR);
	if (info->start == -1)
		return (TIMEERR);
	if (ac == 6)
	{
		info->max_eat = ft_atoi(av[5]);
		if (info->max_eat <= 0)
			return (ARGERR);
	}
	return (0);
}
