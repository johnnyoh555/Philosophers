/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:45:42 by jooh              #+#    #+#             */
/*   Updated: 2023/12/06 19:48:59 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_info *info, t_philo *philo)
{
	sem_wait(philo->sem);
	ft_printf(info, philo, "has taken a fork", 4);
	sem_wait(philo->sem);
	ft_printf(info, philo, "has taken a fork", 4);
	ft_printf(info, philo, "is eating", 0);
	time_go(info, philo, info->eat_time, 1);
	sem_post(philo->sem);
	sem_post(philo->sem);
}

void	waitingline(t_philo *philo)
{
	sem_wait(philo->info->s);
	sem_post(philo->info->s);
	while (1)
	{
		if (philo->info->start <= get_time())
			break ;
		usleep(100);
	}
	sem_wait(philo->checker);
	philo->last_eat = get_time();
	sem_post(philo->checker);
	if (philo->id % 2 == 1)
		usleep(philo->info->eat_time * 500);
}

void	*patern(void *lst)
{
	t_philo	*philo;

	philo = lst;
	waitingline(philo);
	while (1)
	{
		eating(philo->info, philo);
		philo->eat++;
		if (philo->info->max_eat && philo->eat == philo->info->max_eat)
			exit(0);
		ft_printf(philo->info, philo, "is sleeping", 3);
		time_go(philo->info, philo, philo->info->slp_time, 0);
		ft_printf(philo->info, philo, "is thinking", 2);
		usleep(100);
	}
}

void	monitering(t_info *info, t_philo *philo)
{
	long	deadline;
	long	now;

	while (1)
	{
		now = get_time();
		sem_wait(philo->checker);
		deadline = philo->last_eat + info->die_time;
		if (now > deadline)
			ft_printf(info, philo, "died", 1);
		sem_post(philo->checker);
		usleep(200);
	}
	sem_post(philo->checker);
}

void	sitdown(t_info *info, t_philo *philo)
{
	philo->last_eat = get_time() + 100;
	info->pid_flag[philo->id] = 0;
	info->pid[philo->id] = fork();
	if (info->pid[philo->id] == 0)
	{
		pthread_create(philo->thread, 0, patern, philo);
		monitering(info, philo);
		pthread_join(*(philo->thread), 0);
		exit(0);
	}
}
