/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:25:05 by jooh              #+#    #+#             */
/*   Updated: 2023/12/22 13:18:41 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*str1 == 0 && *str2 == 0)
			return (0);
		if (*str1 != *str2)
			return (*str1 - *str2);
		n--;
		str1++;
		str2++;
	}
	return (0);
}

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static int	check_size(char *str, int minus, int i)
{
	while (*str == '0')
		str++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (ARGERR);
		i++;
	}
	if (minus)
	{
		if (ft_strlen(str) > 10)
			return (ARGERR);
		if (ft_strlen(str) == 10 && ft_strncmp(str, "2147483648", 10) > 0)
			return (ARGERR);
	}
	else
	{
		if (ft_strlen(str) > 10)
			return (ARGERR);
		if (ft_strlen(str) == 10 && ft_strncmp(str, "2147483647", 10) > 0)
			return (ARGERR);
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int		minus;
	long	value;

	value = 0;
	minus = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus *= -1;
		str++;
	}
	if (*str == 0 || check_size(str, minus, 0))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		value *= 10;
		value += *str - '0';
		str++;
	}
	return ((int)(value * minus));
}
