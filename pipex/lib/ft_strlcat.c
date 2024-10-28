/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:10:33 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/24 22:50:52 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	j = 0;
	if (!dst && dstsize == 0)
		return (src_len);
	if (dstsize < dst_len)
		return (dstsize + src_len);
	if (!dst || !src)
		return (0);
	while (dst[i] && i < dstsize)
		i++;
	while (src[j] && (i + j < dstsize - 1) && dstsize != 0)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst_len + src_len);
}
