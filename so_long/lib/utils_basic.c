/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:22:43 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/26 12:03:06 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_printchar(int c)
{
	write (1, &c, 1);
	return (1);
}

size_t	ft_printstr(char *s)
{
	if (!s)
		return (ft_printstr("(null)"));
	if (write (1, s, ft_strlen(s)) == -1)
		return (-1);
	return (ft_strlen(s));
}
