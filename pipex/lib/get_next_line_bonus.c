/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:31:06 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/24 22:55:08 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_gnl(char *str)
{
	char	*ret;
	size_t	len_str;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	len_str = ft_strlen(str);
	if (str[0] == '\0')
		len_str = 0;
	ret = malloc(sizeof(char) * (len_str + 1));
	if (!ret)
		return (NULL);
	while (str[i] && i < len_str)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static char	*extract_word(char *str, char *ret_1, size_t len)
{
	size_t	i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (!str)
	{
		free(ret_1);
		return (NULL);
	}
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	while (str[i] && i < len)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	free(ret_1);
	return (ret);
}

static char	*rest_stack(char *stack, size_t len)
{
	char	*new_stack;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!stack)
		return (NULL);
	new_stack = NULL;
	while (stack[len + i])
		i++;
	new_stack = malloc(sizeof(char) * (i + 1));
	if (!new_stack)
		return (NULL);
	while (stack[len + j])
	{
		new_stack[j] = stack[len + j];
		j++;
	}
	new_stack[j] = '\0';
	free(stack);
	return (new_stack);
}

static char	*ft_get_line(char *ret, int fd, int is_new, size_t len_file)
{
	static char	*stack[255];
	char		read_from_file[BUFFER_SIZE + 1];
	size_t		len;

	if (!ret || fd < 0)
		return (NULL);
	if (stack[fd] == NULL)
		stack[fd] = ft_strdup("");
	while (is_new == -1)
	{
		len_file = read(fd, read_from_file, BUFFER_SIZE);
		if (len_file == 0 || (int)len_file == -1)
			break ;
		read_from_file[len_file] = '\0';
		stack[fd] = ft_strjoin_gnl(stack[fd], read_from_file, &is_new);
	}
	len = ft_find_nl(stack[fd]);
	ret = extract_word(stack[fd], ret, len);
	stack[fd] = rest_stack(stack[fd], len);
	if (!ret)
		return (ft_free_an_ret_null(ret, 0, 0));
	if ((ret[0] == '\0') || (((int)len_file) == -1))
		return (ft_free_an_ret_null(ret, &stack[fd], 0));
	return (ret);
}

char	*get_next_line(int fd)
{
	char	*ret;

	ret = NULL;
	if ((fd < 0 || fd >= FOPEN_MAX) || BUFFER_SIZE <= 0)
		return (NULL);
	ret = ft_get_line(ret, fd, -1, 0);
	if (ret == NULL)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}
