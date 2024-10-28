/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:39:31 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/02 17:00:43 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

size_t	not_null_terminated_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len])
		++len;
	if (dstsize == 0)
		return (len);
	i = -1;
	while (src[++i] && i < dstsize)
		dst[i] = src[i];
	return (len);
}

void	bzero_with_spaces(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n - 1)
	{
		*(unsigned char *)(s + i) = ' ';
		++i;
	}
	*(unsigned char *)(s + i) = '\0';
}

void	*calloc_with_spaces(size_t count, size_t size)
{
	void	*calloc;

	calloc = malloc(count * size);
	if (!calloc)
		return (NULL);
	bzero_with_spaces(calloc, count * size);
	return (calloc);
}
