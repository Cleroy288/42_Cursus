/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:33 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/06 15:45:06 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_count_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	int				i;

	i = ft_count_digits(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	if (n < 0)
		nb = -n;
	else
		nb = n;
	str[i--] = '\0';
	if (nb == 0)
		str[i] = '0';
	while (nb != 0)
	{
		str[i--] = nb % 10 + '0';
		nb /= 10;
	}
	if (n < 0)
		str[i] = '-';
	return (str);
}
