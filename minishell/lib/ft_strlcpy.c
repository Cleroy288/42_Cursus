/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:30:35 by chleroy           #+#    #+#             */
/*   Updated: 2023/08/24 18:04:00 by hubrygo          ###   ########.fr       */
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
