/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_recursive.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:16:26 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/11 14:40:45 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printhex(unsigned int nb, char *base, size_t *len)
{
	if (nb < 16)
		*len += ft_putchar(base[nb]);
	else
	{
		ft_printhex(nb / 16, base, len);
		ft_printhex(nb % 16, base, len);
	}
}

size_t	ft_putnbr_base(long long int nbr, char *base, size_t base_len)
{
	size_t	len;

	len = 0;
	if (nbr < 0)
	{	
		ft_printhex((unsigned int)nbr, base, &base_len);
		return (8);
	}
	else
		return (ft_putnbr_hex(nbr, base, base_len));
	return (len);
}
