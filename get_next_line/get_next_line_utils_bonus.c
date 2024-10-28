/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:31:45 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/25 12:32:00 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_free_an_ret_null(char *str, char **str2, char *buffer)
{
	if (str || str2 || buffer)
	{
		if (str)
			free(str);
		if (str2)
		{
			free(*str2);
			*str2 = NULL;
		}
		if (buffer)
		{
			free(buffer);
		}
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2, int *is_new_line)
{
	size_t	len_s1;
	size_t	len_str;
	char	*str;

	if (!s1 || !s2)
		return (ft_free_an_ret_null(s1, 0, 0));
	str = NULL;
	len_s1 = ft_strlen(s1);
	len_str = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (len_str + 1));
	if (!str)
		return (NULL);
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	if (*(str - 1) == '\n' && len_str > 0)
		*is_new_line = 1;
	free(s1 - len_s1);
	return (str - len_str);
}

size_t	ft_find_nl(char *str)
{
	size_t	i;
	size_t	len_str;

	i = 0;
	if (!str)
		return (-1);
	len_str = ft_strlen(str);
	while (str[i] && i < len_str)
	{
		if (str[i] == '\n' || str[i] == '\0')
			return (i + 1);
		i++;
	}
	return (i);
}
