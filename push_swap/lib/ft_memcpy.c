/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:43:07 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/08 15:45:12 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t					i;
	const unsigned char		*s;
	unsigned char			*d;

	i = -1;
	s = src;
	d = dst;
	if (!dst && !src)
		return (NULL);
	while (++i < n)
		d[i] = s[i];
	return (dst);
}
