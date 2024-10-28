/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_without_one_lettre.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:51:32 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:56:35 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_make_str_without_one_letter(char *str, char c)
{
	int		i;
	int		j;
	int		count;
	char	*ret;

	count = 0;
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	ret = malloc(sizeof(char) * (ft_strlen(str) - count + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	i = -1;
	while (str[++i])
	{
		if (str[i] != c)
			ret[j++] = str[i];
	}
	ret[j] = '\0';
	return (ret);
}

char	ft_check_for_sec_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == '"')
			return (str[i]);
		i ++;
	}
	return (0);
}

char	*ft_treat_command_for_echo(char *s)
{
	char	**str;
	char	*new;
	int		i;

	i = 0;
	str = ft_split(s, '|');
	while (str[i])
	{
		if (ft_strncmp(str[i], "echo", 4) == 0)
			new = ft_strdup(str[i]);
		i++;
	}
	if (g_data.input_file)
	{
		new = ft_str_without_w(new, g_data.input_file);
		new = ft_make_str_without_one_letter(new, '<');
	}
	if (g_data.output_file)
	{
		new = ft_str_without_w(new, g_data.output_file);
		new = ft_make_str_without_one_letter(new, '>');
	}
	return (new);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

char	*ft_find_in_env(char *s)
{
	int		i;
	char	*loc;

	i = 0;
	while (g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], s, ft_strlen(s)))
		{
			loc = ft_strchr(g_data.env[i], '=');
			if (loc)
				return (ft_strdup(loc + 1));
		}
		i++;
	}
	return (NULL);
}
