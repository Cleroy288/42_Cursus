/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:38:39 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/05 13:05:10 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	k;

	k = ft_strlen(str);
	while (k && str && str[k] != (char)c && k--)
		;
	if (str[k] == (char)c)
		return ((char *)&str[k]);
	return (NULL);
}
