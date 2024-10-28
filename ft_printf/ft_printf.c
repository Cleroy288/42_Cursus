/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:08:57 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/11 14:37:42 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_is_in(char c, char *pos)
{
	size_t	i;

	i = 0;
	while (pos[i])
	{
		if (c == pos[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_dispatch(va_list ag, char c)
{
	char				*hex_maj;
	char				*hex_min;
	size_t				res;

	hex_maj = "0123456789ABCDEF";
	hex_min = "0123456789abcdef";
	res = 0;
	if (c == 'd' || c == 'i')
		res += ft_putnbr(va_arg(ag, int));
	else if (c == 'x')
		res += ft_putnbr_base((long long int)va_arg(ag, int), hex_min, 16);
	else if (c == 'X')
		res += ft_putnbr_base((long long int)va_arg(ag, int), hex_maj, 16);
	else if (c == 'c')
		res += ft_putchar(va_arg(ag, int));
	else if (c == 's')
		res += ft_putstr(va_arg(ag, char *));
	else if (c == '%')
		res += ft_putchar('%');
	else if (c == 'p')
		res += ft_putmem(va_arg(ag, unsigned long int), "0123456789abcdef");
	if (c == 'u')
		res += ft_putnbr_u(va_arg(ag, unsigned int));
	return (res);
}

int	ft_printf(char const *str, ...)
{
	size_t	i;
	size_t	res;
	va_list	ag;

	i = 0;
	res = 0;
	va_start(ag, str);
	while (str[i])
	{
		if (str[i] == '%' && ft_is_in(str[i + 1], "cspdiuxX%") == 1)
		{
			res += ft_dispatch(ag, str[i + 1]);
			i += 2;
		}
		else
		{
			res += ft_putchar(str[i]);
			i++;
		}
	}
	va_end(ag);
	return (res);
}
