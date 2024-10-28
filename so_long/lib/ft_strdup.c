/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:15:03 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/03 17:03:57 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*s2;
	size_t			i;
	size_t			len;

	i = 0;
	len = ft_strlen(s);
	if (!s)
		return (0);
	s2 = malloc((sizeof(char) * (len + 1)));
	if (!s2)
		return (NULL);
	while (s[i] && i < ft_strlen(s))
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
