/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:57:55 by jooh              #+#    #+#             */
/*   Updated: 2023/12/17 15:18:10 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	make_checker_sema(t_info *info)
{
	char	*nbr;
	char	*str;
	int		i;

	sem_unlink("s_sema");
	info->s = sem_open("s_sema", O_CREAT, 0644, 1);
	info->checker = malloc(sizeof(sem_t *) * info->humans);
	if (info->checker == 0)
		return (0);
	i = 0;
	while (i < info->humans)
	{
		nbr = ft_itoa(i);
		str = ft_strjoin("checker_sema", nbr);
		sem_unlink(str);
		info->checker[i] = sem_open(str, O_CREAT, 0644, 1);
		if (info->checker[i] == SEM_FAILED)
			return (1);
		free(nbr);
		free(str);
		i++;
	}
	return (0);
}

int	make_philos(t_info *info, t_philo *philo)
{
	int		i;

	sem_unlink("forks_sema");
	sem_unlink("printer_sema");
	info->sem = sem_open("forks_sema", O_CREAT, 0644, info->humans);
	info->printer = sem_open("printer_sema", O_CREAT, 0644, 1);
	if (info->sem == SEM_FAILED || info->printer == SEM_FAILED
		|| make_checker_sema(info))
		return (SEMAERR);
	if (info->checker == 0)
		return (ALLOCERR);
	i = -1;
	while (++i < info->humans)
	{
		philo[i].info = info;
		philo[i].eat = 0;
		philo[i].id = i;
		philo[i].sem = info->sem;
		philo[i].printer = info->printer;
		philo[i].checker = info->checker[i];
		philo[i].thread = malloc(sizeof(pthread_t));
		if (philo[i].thread == 0)
			return (ALLOCERR);
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
	info->pid = malloc(sizeof(pid_t) * info->humans);
	info->pid_flag = malloc(sizeof(int) * info->humans);
	if (info->pid == 0 || info->pid_flag == 0)
		return (ALLOCERR);
	return (0);
}
