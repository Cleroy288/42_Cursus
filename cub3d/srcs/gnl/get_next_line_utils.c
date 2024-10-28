/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:26:21 by noloupe           #+#    #+#             */
/*   Updated: 2023/01/23 15:19:10 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	copy(char *dst, char *src, int size)
{
	int	i;

	if (size < 1)
		return ;
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < size)
	{
		dst[i] = '\0';
		i++;
	}
}

int	check_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

char	*join(char *line, char *buffer, int size)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	if (!line)
		return (NULL);
	len = ft_strlen(line) + size;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
	{
		free(line);
		return (NULL);
	}
	i = -1;
	while (line[++i])
		str[i] = line[i];
	free(line);
	j = -1;
	while (i < len)
		str[i++] = buffer[++j];
	str[i] = '\0';
	return (str);
}
