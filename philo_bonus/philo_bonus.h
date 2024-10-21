/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:25:54 by jooh              #+#    #+#             */
/*   Updated: 2023/12/05 17:14:57 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <semaphore.h>
# include <signal.h>

# define ARGERR 1
# define SEMAERR 2
# define ALLOCERR 3
# define TIMEERR 4
# define THREADERR 5

typedef struct s_info
{
	int				humans;
	int				die_time;
	int				eat_time;
	int				slp_time;
	int				max_eat;
	long			start;
	pid_t			*pid;
	int				*pid_flag;
	sem_t			*sem;
	sem_t			*printer;
	sem_t			*s;
	sem_t			**checker;
}	t_info;

typedef struct s_philo
{
	t_info			*info;
	int				eat;
	int				id;
	sem_t			*sem;
	sem_t			*printer;
	sem_t			*checker;
	long			last_eat;
	pthread_t		*thread;
}	t_philo;

// main_bonus.c
void	ft_printf(t_info *info, t_philo *philo, char *str, int flag);
int		time_go(t_info *info, t_philo *philo, long sleep, int i);
long	get_time(void);

// thread_bonus.c
void	sitdown(t_info *info, t_philo *philo);
void	monitering(t_info *info, t_philo *philo);
void	*patern(void *lst);
void	eating(t_info *info, t_philo *philo);

// parsing_bonus.c
int		init_info(t_info *info, char *av[], int ac);
int		make_philos(t_info *info, t_philo *philo);
int		make_checker_sema(t_info *info);

// atoi_bonus.c
int		ft_atoi(char *str);
int		check_size(char *str, int minus, int i);
int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// utils_bonus.c
char	*ft_itoa(int n);
char	*ft_strjoin(char *s1, char *s2);

// end_seq_bonus.c
void	end_seq(t_info *info, t_philo *philo);
void	end_checker(t_info *info, t_philo *philo);
void	waiting(t_info *info);
int		err_seq(t_info *info, t_philo *philo, int i);
void	kill_seq(t_info *info);

#endif