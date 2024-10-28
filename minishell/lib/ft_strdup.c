/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:15:03 by chleroy           #+#    #+#             */
/*   Updated: 2023/09/12 17:47:32 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;
	size_t	i;
	size_t	len;

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

char	*ft_strndup(const char *s, size_t n)
{
	size_t		len;
	char		*new_str;

	len = ft_strlen(s);
	if (n < len)
		len = n;
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, s, len);
	new_str[len] = '\0';
	return (new_str);
}
