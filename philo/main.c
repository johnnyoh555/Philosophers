/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:24:59 by jooh              #+#    #+#             */
/*   Updated: 2023/12/17 14:57:46 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_philo	*philo;
	t_info	info;
	int		i;

	philo = 0;
	memset(&info, 0, sizeof(t_info));
	if ((ac != 5 && ac != 6) || init_info(&info, av, ac))
		return (err_seq(&info, philo, ARGERR));
	i = make_forks(&info);
	if (i)
		return (err_seq(&info, philo, i));
	philo = malloc(sizeof(t_philo) * info.humans);
	if (philo == 0)
		return (err_seq(&info, philo, ALLOCERR));
	i = make_philos(&info, philo);
	if (i)
		return (err_seq(&info, philo, i));
	pthread_mutex_lock(&info.startline);
	i = sitdown(&info, philo);
	end_seq(&info, philo);
	return (0);
}
