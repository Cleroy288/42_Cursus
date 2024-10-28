/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:56:09 by chleroy           #+#    #+#             */
/*   Updated: 2023/07/27 12:56:11 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	int			i;
	long long	r;
	int			k;

	i = -1;
	r = 0;
	k = 1;
	while (str[++i])
		if (str[i] > '9' || str[i] < '0')
			return (-1);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - 48);
		if (r > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)r * k);
}

int	ft_error(char *str, int i)
{
	printf("%s\n", str);
	return (i);
}

int	ft_get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(int time)
{
	int	start;

	start = ft_get_current_time();
	while ((ft_get_current_time() - start) < time)
		usleep(100);
}

long long	ft_time_diff(long long past, long long pres)
{
	return (pres - past);
}
