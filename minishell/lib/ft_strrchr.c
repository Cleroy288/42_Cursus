/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:38:39 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/24 22:53:08 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	k;

	if (!str)
		return (NULL);
	k = ft_strlen(str);
	while (k && str && str[k] != (char)c && k--)
		;
	if (str[k] == (char)c)
		return ((char *)&str[k]);
	return (NULL);
}
