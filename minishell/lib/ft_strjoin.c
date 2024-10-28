/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:01:08 by chleroy           #+#    #+#             */
/*   Updated: 2023/09/12 20:46:50 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_new(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strlen(s2));
	if (!s2)
		return (ft_strlen(s1));
	while (s1[++i])
		;
	while (s2[++j])
		;
	return (i + j);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			len_str;
	size_t			i;
	unsigned char	*str;

	str = NULL;
	len_str = -1;
	i = -1;
	if (!s1 && !s2)
		return (0);
	if (s1 || s2)
		str = malloc(sizeof(char) * (ft_strlen_new(s1, s2) + 1));
	if (!str)
		return (0);
	if (s1)
		while (s1[++i] && ++len_str == i)
			str[len_str] = s1[i];
	i = -1;
	if (s2)
		while (s2[++i] && ++len_str >= i)
			str[len_str] = s2[i];
	str[len_str + 1] = '\0';
	return ((char *)str);
}

char	*ft_strjoin_free_both(char *s1, char *s2)
{
	size_t			len_str;
	size_t			i;
	unsigned char	*str;

	str = NULL;
	len_str = -1;
	i = -1;
	if (!s1 && !s2)
		return (0);
	if (s1 || s2)
		str = malloc(sizeof(char) * (ft_strlen_new(s1, s2) + 1));
	if (!str)
		return (0);
	if (s1)
		while (s1[++i] && ++len_str == i)
			str[len_str] = s1[i];
	i = -1;
	if (s2)
		while (s2[++i] && ++len_str >= i)
			str[len_str] = s2[i];
	str[len_str + 1] = '\0';
	free(s1);
	free(s2);
	return ((char *)str);
}
