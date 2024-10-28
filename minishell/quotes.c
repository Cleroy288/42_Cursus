/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:00:15 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 18:11:47 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_is_dollars(char *s, int *i, char *ret)
{
	int		j;
	char	*variable;
	char	*value;

	j = 0;
	variable = malloc(sizeof(char) * 100);
	if (!variable)
		exit(EXIT_FAILURE);
	if (s[(*i)] != 39)
		(*i)++;
	while (s[(*i)] != 32 && s[(*i)] != '\0' && variable[j]
		&& (s[(*i)] != 39) && (*i) < (int)ft_strlen(s))
	{
		if (s[(*i)] && variable[j] && s[(*i)] == '"' && s[(*i) + 1])
			(*i)++;
		variable[j++] = s[(*i)++];
	}
	variable[j] = '\0';
	ret = ft_is_dollars_sec_part(&value, &variable, ret, s);
	return (ret);
}

char	*ft_set_print_variabels(char *s)
{
	int		i;
	char	*ret;

	if (!s)
		return (NULL);
	i = 0;
	ret = NULL;
	while (s[i] && i < (int)ft_strlen(s))
	{
		if (s[i] == '$')
		{
			ret = ft_is_dollars(s, &i, ret);
			if (!ret)
				return (NULL);
		}
		if (s[i])
			i++;
	}
	if (!ret)
		ret = ft_strdup(s);
	ret = ft_last_operation_remove_single_quotes(ret);
	free(s);
	return (ret);
}

char	*ft_takeout_part_2(char *s, int *k, char *ret, int i)
{
	int		in_double_quotes;
	char	*final;

	while (s[i])
	{
		if (s[i] == '"')
			in_double_quotes = !in_double_quotes;
		else if (s[i] == 39 && !in_double_quotes)
		{
			if (s[i + 1] == '$')
			{
				ret[(*k)++] = s[i++];
				while (s[i] && s[i] != 39)
					ret[(*k)++] = s[i++];
			}
			else if (i++)
				continue ;
		}
		ret[(*k)++] = s[i];
		if (s[i])
			i++;
	}
	final = ft_strdup(ret);
	free(ret);
	return (final);
}

char	*ft_takeout_single_quotes(char *s)
{
	char	*ret;
	int		k;

	if (!s)
		return (NULL);
	ret = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	k = 0;
	ret = ft_takeout_part_2(s, &k, ret, 0);
	if (!ret)
		return (NULL);
	ret[k] = '\0';
	return (ret);
}

int	ft_go_to_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i] && i != 39)
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}
