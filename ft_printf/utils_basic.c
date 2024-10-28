/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:22:43 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/11 15:06:05 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

size_t	ft_putchar(int c)
{
	write (1, &c, 1);
	return (1);
}

size_t	ft_putstr(char *s)
{
	if (!s)
		return (ft_putstr("(null)"));
	if (write (1, s, ft_strlen(s)) == -1)
		return (-1);
	return (ft_strlen(s));
}
