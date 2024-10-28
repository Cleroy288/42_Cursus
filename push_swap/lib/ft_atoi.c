/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:09:17 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/19 10:42:22 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

static size_t	ft_p(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	return (i);
}

static int	ft_sign(const char *str)
{
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
	while (str[i] && ft_is_space(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	return (sign);
}

long	ft_atoi(const char *str)
{
	long int	i;
	long int	res;
	long int	sign;

	res = 0;
	sign = ft_sign(str);
	i = ft_p(str);
	if (ft_strncmp(str, "-2147483648", 12) == 0)
		return (-2147483648);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sign);
}
