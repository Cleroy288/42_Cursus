/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:59:59 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/24 22:40:13 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	if (!b || c == 0)
		return (NULL);
	ptr = (unsigned char *)b;
	i = 0;
	while (len > 0)
	{
		ptr[i] = (unsigned char)c;
		len--;
		i++;
	}
	return (b);
}
