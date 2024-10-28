/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:19:15 by chleroy           #+#    #+#             */
/*   Updated: 2023/09/19 10:32:21 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_ret_ptb(unsigned long long int nb, size_t base_len)
{
	size_t	len;

	len = 0;
	while (nb)
	{
		nb /= base_len;
		len++;
	}
	return (len);
}

size_t	ft_putnbr_hex(unsigned long int nbr, char *base, size_t base_len)
{
	size_t					len;
	unsigned long long int	nb;

	nb = nbr;
	len = ft_ret_ptb(nb, base_len);
	if (nbr == 0)
		return (ft_printchar('0'));
	if ((nbr >= base_len))
	{
		ft_putnbr_hex(nbr / base_len, base, base_len);
		nbr %= base_len;
	}
	if (nbr < base_len)
		write (1, &base[nbr], 1);
	return (len);
}

size_t	ft_putmem(unsigned long int ptr, char *base)
{
	size_t	base_len;
	size_t	res;

	res = 0;
	if (!ptr || !base)
		return (ft_printstr("0x0"));
	base_len = ft_strlen(base);
	if (base_len < 2)
		return (0);
	res = ft_printstr("0x");
	res += ft_putnbr_hex((unsigned long int)ptr, base, base_len);
	return (res);
}
