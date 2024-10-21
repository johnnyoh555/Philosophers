/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:13:13 by jooh              #+#    #+#             */
/*   Updated: 2023/12/04 20:12:09 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	trans(int long n, char *arr, int j)
{	
	int	i;

	if (n)
	{
		trans(n / 10, arr, j - 1);
		i = n % 10;
		arr[j - 1] = '0' + i;
	}
}

static void	to_char(int long n, char *arr, int j)
{
	if (n == 0)
	{
		arr[0] = '0';
		arr[1] = 0;
		return ;
	}
	else if (n < 0)
	{
		n *= -1;
		arr[0] = '-';
		arr[j] = 0;
		trans(n, arr, j);
	}
	else
	{
		arr[j] = 0;
		trans(n, arr, j);
	}
}

static int	how_much(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		size;

	size = how_much(n);
	if (n > 0)
		arr = malloc(size + 1);
	else
		arr = malloc(size + 2);
	if (arr == 0)
		return (0);
	if (n < 0)
		to_char((int long)n, arr, size + 1);
	else
		to_char((int long)n, arr, size);
	return (arr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*arr;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	arr = malloc(len + 1);
	if (arr == 0)
		return (0);
	while (*s1)
	{
		*arr = *s1;
		arr++;
		s1++;
	}
	while (*s2)
	{
		*arr = *s2;
		arr++;
		s2++;
	}
	*arr = 0;
	return (arr - len);
}
