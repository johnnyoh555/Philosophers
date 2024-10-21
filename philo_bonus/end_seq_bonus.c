/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_seq_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:22:21 by jooh              #+#    #+#             */
/*   Updated: 2023/12/05 17:59:02 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	err_seq(t_info *info, t_philo *philo, int i)
{
	char	*str;

	end_seq(info, philo);
	if (i == 1)
		str = "argument: wrong arguments";
	else if (i == 2)
		str = "semaphore: fail to make semaphore";
	else if (i == 3)
		str = "malloc: fail to allocate";
	else if (i == 4)
		str = "gettimeofday: fail to get time";
	else
		str = "thread: fail to create a thread";
	printf("\e[31mphilo: %s\e[0m\n", str);
	exit(i);
}

void	waiting(t_info *info)
{
	int		i;
	int		j;
	int		status;

	i = -1;
	while (++i < info->humans)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 0)
		{
			j = 0;
			while (j < info->humans)
			{
				kill(info->pid[j], SIGKILL);
				waitpid(info->pid[j], &status, 0);
				j++;
			}
		}
	}
}

void	end_checker(t_info *info, t_philo *philo)
{
	int		i;
	char	*nbr;
	char	*str;

	i = 0;
	while (i < info->humans)
	{
		if (philo && philo[i].thread && info->checker)
		{
			sem_close(info->checker[i]);
			nbr = ft_itoa(i);
			str = ft_strjoin("checker_sema", nbr);
			if (nbr == 0 || str == 0)
				err_seq(info, philo, ALLOCERR);
			sem_unlink(str);
			free(nbr);
			free(str);
			free(philo[i].thread);
		}
		i++;
	}
}

void	end_seq(t_info *info, t_philo *philo)
{
	sem_close(info->s);
	sem_unlink("s_sema");
	sem_post(philo->printer);
	sem_close(info->printer);
	sem_unlink("printer_sema");
	sem_close(info->sem);
	sem_unlink("forks_sema");
	end_checker(info, philo);
	if (philo)
		free(philo);
	if (info->pid)
		free(info->pid);
	if (info->pid_flag)
		free(info->pid_flag);
	if (info->checker)
		free(info->checker);
}
