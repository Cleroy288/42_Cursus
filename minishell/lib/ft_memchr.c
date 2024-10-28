/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:38:22 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/24 22:38:36 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*str_1;

	if (!str || c == 0 || n == 0)
		return (NULL);
	str_1 = (unsigned char *)str;
	i = -1;
	while (++i < n)
	{
		if (((unsigned char *)str_1)[i] == (unsigned char)c)
			return ((void *)(str_1 + i));
	}
	return (0);
}
