/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:30:35 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/24 22:51:28 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dst || !src || dstsize == 0)
		return (0);
	if (dstsize == 0)
		while (src[i])
			i++;
	if (dstsize != 0)
	{
		while (src[i] && dstsize > 1)
		{	
			dst[i] = src[i];
			i++;
			dstsize--;
		}
		dst[i] = '\0';
		if (src[i])
			while (src[i])
				i++;
	}
	return (i);
}
