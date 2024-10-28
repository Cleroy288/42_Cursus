/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:12:29 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/05 13:37:15 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = -1;
	while ((unsigned char)str[++i] != (char)c)
		if ((unsigned char)str[i] == 0)
			return (NULL);
	return ((char *)&str[i]);
}
