/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:16:26 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/24 22:47:32 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printhex(unsigned int nb, char *base, size_t *len)
{
	if (!base || len == 0)
		return ;
	if (nb < 16)
		*len += ft_printchar(base[nb]);
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
	if (!base || base_len == 0)
		return (0);
	if (nbr < 0)
	{	
		ft_printhex((unsigned int)nbr, base, &base_len);
		return (8);
	}
	else
		return (ft_putnbr_hex(nbr, base, base_len));
	return (len);
}
