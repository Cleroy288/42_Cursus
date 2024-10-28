/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:12:29 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/24 22:48:54 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = -1;
	if (!str || c == 0)
		return (NULL);
	while ((unsigned char)str[++i] != (char)c)
		if ((unsigned char)str[i] == 0)
			return (NULL);
	return ((char *)&str[i]);
}
