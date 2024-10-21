/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:12:02 by jooh              #+#    #+#             */
/*   Updated: 2023/12/10 13:12:39 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;
	int				time;

	if (gettimeofday(&tv, 0) == -1)
		return (-1);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

int	time_go(t_info *info, t_philo *philo, long sleep, int i)
{
	long	start;

	start = get_time();
	if (i == 1)
	{
		if (check_dead(philo->info, philo))
			return (0);
		philo->last_eat = start;
		philo->eat++;
	}
	if (start + sleep <= philo->last_eat + info->die_time)
		usleep(sleep * 800);
	while (check_dead(info, philo) == 0 && start + sleep > get_time())
		usleep(200);
	return (0);
}
