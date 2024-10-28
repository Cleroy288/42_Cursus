/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:26:55 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 16:34:25 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_args_in_struct(void)
{
	int		i;

	i = 0;
	g_data.commands_count = 0;
	while (g_data.commands[i])
		i++;
	g_data.commands_count = i;
}

int	ft_search_for_character(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			j++;
		i++;
	}
	if (j % 2 == 0)
		return (1);
	return (0);
}

char	*ft_strstr(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	if (!*needle)
		return (haystack);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			j++;
			if (!needle[j])
				return (haystack + i);
		}
		i++;
	}
	return (NULL);
}

char	*ft_join_and_set_char(char *s1, char *s2, char c)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!ret)
		exit(EXIT_FAILURE);
	while (s1 && s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = c;
	i++;
	while (s2 && s2[j])
	{
		ret [i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}

char	*ft_make_str_without_one_letter_free_str(char *str, char letter)
{
	int		i;
	int		k;
	char	*new;

	i = 0;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		exit(EXIT_FAILURE);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] != letter)
		{
			new[k] = str[i];
			k++;
		}
		i++;
	}
	new[k] = '\0';
	free(str);
	return (new);
}
