/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:38:29 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:39:24 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_make_word(char *s, size_t *index, char *sp)
{
	size_t	start;
	size_t	end;
	char	c;

	start = *index;
	if (s[*index] && ft_is_on_char(s[*index], sp))
	{
		c = s[*index];
		start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		if (s[end])
			*index = end + 1;
		else
			*index = end;
	}
	else
	{
		while (s[*index] && s[*index] != ' ' && !ft_is_on_char(s[*index], sp))
			(*index)++;
		end = *index;
	}
	return (ft_return_value(end, start, s));
}

char	**ft_special_split(char *s, char *sp)
{
	size_t	i;
	int		j;
	int		nb_of_word;
	char	**ret;

	i = 0;
	j = 0;
	nb_of_word = ft_nb_of_words(s, sp);
	ret = (char **)malloc(sizeof(char *) * (nb_of_word + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	while (j < nb_of_word)
	{
		ret[j] = ft_make_word(s, &i, sp);
		while (s[i] && s[i] == ' ')
			i++;
		j++;
	}
	ret[nb_of_word] = NULL;
	return (ret);
}

char	*ft_find_argument_in_env_value(char *arg)
{
	int	i;
	int	len;

	len = ft_strlen(arg);
	i = 0;
	while (g_data.env[i])
	{
		if (ft_strncmp(g_data.env[i], arg, len) == 0
			&& g_data.env[i][len] == '=')
			return (g_data.env[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	ft_print_path(char *s)
{
	if (!s)
		return (0);
	if (s && ft_strncmp(s, "$PATH", 5) == 0)
	{
		if (!g_data.word_here_doc)
		{
			if (!s)
				printf("minishell: command not found\n");
			else
			{
				printf("minishell: [%s]", ft_find_line("PATH") + 5);
				printf(": command not found\n");
			}
			return (0);
		}
	}
	return (1);
}

int	full(char *value, char *new_str, int j)
{
	int	len;

	if (!value)
		return (0);
	len = ft_strlen(value);
	new_str = ft_strncpy(new_str + j, value, len);
	if (!new_str)
		return (0);
	return (len);
}
