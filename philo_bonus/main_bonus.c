/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:24:59 by jooh              #+#    #+#             */
/*   Updated: 2023/12/17 14:58:38 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, 0) == -1)
		return (-1);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

int	time_go(t_info *info, t_philo *philo, long sleep, int i)
{
	long	start;
	long	die_time;

	sem_wait(philo->checker);
	if (i == 1)
	{
		if (get_time() > philo->last_eat + info->die_time)
			ft_printf(info, philo, "died", 1);
		philo->last_eat = get_time();
	}
	die_time = philo->last_eat + info->die_time;
	sem_post(philo->checker);
	start = get_time();
	if (start + sleep <= die_time)
		usleep(sleep * 500);
	while (start + sleep > get_time())
		usleep(100);
	return (0);
}

void	ft_printf(t_info *info, t_philo *philo, char *str, int flag)
{
	int	id;

	id = philo->id + 1;
	sem_wait(philo->printer);
	if (flag == 0)
		printf("\e[32m%ld %d %s\e[0m\n", get_time() - info->start, id, str);
	else if (flag == 2)
		printf("\e[33m%ld %d %s\e[0m\n", get_time() - info->start, id, str);
	else if (flag == 3)
		printf("\e[34m%ld %d %s\e[0m\n", get_time() - info->start, id, str);
	else if (flag == 4)
		printf("\e[35m%ld %d %s\e[0m\n", get_time() - info->start, id, str);
	else if (flag == 1)
	{
		printf("\e[31m%ld %d %s\e[0m\n", get_time() - info->start, id, str);
		exit(-1);
	}
	sem_post(philo->printer);
}

int	main(int ac, char *av[])
{
	t_philo	*philo;
	t_info	info;
	int		i;

	philo = 0;
	memset(&info, 0, sizeof(t_info));
	if ((ac != 5 && ac != 6) || init_info(&info, av, ac))
		return (err_seq(&info, philo, ARGERR));
	philo = malloc(sizeof(t_philo) * info.humans);
	if (philo == 0)
		return (err_seq(&info, philo, ALLOCERR));
	i = make_philos(&info, philo);
	if (i)
		return (err_seq(&info, philo, i));
	sem_wait(info.s);
	i = -1;
	while (++i < info.humans)
		sitdown(&info, &(philo[i]));
	sem_post(info.s);
	waiting(&info);
	end_seq(&info, philo);
	return (0);
}
