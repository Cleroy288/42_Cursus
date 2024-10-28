/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:26:09 by noloupe           #+#    #+#             */
/*   Updated: 2022/12/13 16:53:18 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_size(char *str, int *check)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (str[i] == '\0' || str[i] == '\n')
		{
			i++;
			*check = 1;
			break ;
		}
		i++;
	}
	return (i);
}

char	*fct_get_line(char *line, char *save, int *check, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_res;
	int		size;

	read_res = 1;
	while (*check == 0 && read_res > 0)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		read_res = read(fd, buffer, BUFFER_SIZE);
		if (read_res == -1)
		{
			ft_bzero(save, BUFFER_SIZE + 1);
			free(line);
			return (NULL);
		}
		size = get_size(buffer, check);
		copy(save, &buffer[size], BUFFER_SIZE + 1);
		line = join(line, buffer, size);
		if (read_res == 0)
		{
			ft_bzero(save, BUFFER_SIZE + 1);
			return (line);
		}
	}
	return (line);
}

char	*save_dup(char *save, int *size, int *check)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	while (save[len] && save[len] != '\n')
		len++;
	if (save[len] == '\n')
	{
		len++;
		*check = 1;
	}
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = save[i];
		i++;
	}
	str[i] = '\0';
	*size = len;
	return (str);
}

char	*get_next_line(int fd)
{
	static char	save[BUFFER_SIZE + 1];
	char		*line;
	int			size;
	int			check;

	check = 0;
	if (fd > OPEN_MAX || fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = save_dup(save, &size, &check);
	if (!line)
		return (NULL);
	copy(save, &save[size], BUFFER_SIZE + 1);
	line = fct_get_line(line, save, &check, fd);
	if (!line || *line == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
