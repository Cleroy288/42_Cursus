/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:18:34 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/26 12:08:30 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr_u(unsigned int nb)
{
	char			c;
	long long int	n;

	n = nb;
	if (n == 0)
		return (ft_printchar('0'));
	if (n == 4294967295)
	{
		if (write(1, "4294967295", ft_strlen("4294967295")) == -1)
			return (-1);
		return (ft_strlen("4294967295"));
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	c = n % 10 + '0';
	if (write(1, &c, 1) == -1)
		return (-1);
	return (ft_len_nb(nb));
}
