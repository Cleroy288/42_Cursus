/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:41:35 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:43:19 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_len_env_value(char *s)
{
	int		i;
	int		key_len;
	char	*equal_sign_ptr;
	int		len;

	i = 0;
	if (!s)
		return (0);
	key_len = ft_strlen(s);
	while (g_data.env[i])
	{
		equal_sign_ptr = ft_strchr(g_data.env[i], '=');
		if (equal_sign_ptr && ft_strncmp(g_data.env[i], s, key_len) == 0
			&& g_data.env[i][key_len] == '=')
		{
			free(s);
			len = ft_strlen(equal_sign_ptr + 1);
			return (len);
		}
		i++;
	}
	free(s);
	return (0);
}

int	ft_len_word(char *s, int index)
{
	int		i;
	char	*word;

	i = 0;
	if (!s)
		return (0);
	while (s[index + i] && (s[index + i] != 32
			&& s[index + i] != 39 && s[index + i] != '"'))
		i++;
	word = ft_substr(s, index, i);
	if (!word)
		return (0);
	return (ft_find_len_env_value(word));
}

int	ft_len_new_str(char *s)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] != '$' && s[i + 1] != 32)
		{
			i++;
			len += ft_len_word(s, i);
			while (s[i] && s[i] != ' ' && s[i] != '$')
				i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len + ft_strlen(s) + 300);
}

char	*get_env_var_name(char *s, int *i)
{
	int		start;

	start = (*i)++;
	while (s[*i] && ft_isalnum(s[*i]))
		(*i)++;
	return (ft_substr(s, start + 1, *i - start - 1));
}

void	append_value_or_var(char *new_str,
	int *j, char *value, int start)
{
	int		i;

	i = 0;
	if (value)
	{
		while (value[i])
		{
			new_str[(*j)++] = value[i];
			i++;
		}
	}
	else
	{
		while (start < i)
			new_str[(*j)++] = g_data.sub_var->s[start++];
	}
}
