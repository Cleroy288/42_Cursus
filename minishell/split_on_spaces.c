/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_on_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:27:24 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:32:37 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_valid_spaces(char *s, char *c, int *i)
{
	int	nb;

	nb = 1;
	while (s[*i])
	{
		if ((s[*i] == '"' || s[*i] == '\'') && *c == 0)
		{
			*c = s[*i];
			(*i)++;
			while (s[*i] && s[*i] != *c)
				(*i)++;
			if (s[*i] == *c)
				*c = 0;
		}
		else if (s[*i] == 32 && *c == 0)
			nb++;
		if (s[*i])
			(*i)++;
	}
	return (nb);
}

int	nb_of_word_for_valid_spaces(char *s)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	if (!s)
		return (0);
	return (count_valid_spaces(s, &c, &i));
}

int	handle_quotes(char *s, char *c, int *j)
{
	*c = s[*j];
	(*j)++;
	while (s[*j] && s[*j] != *c)
		(*j)++;
	if (s[*j] == *c)
		*c = 0;
	return (*j);
}

char	*find_next_word(char *s, int *i, char *c)
{
	int	start;
	int	j;

	start = *i;
	j = *i;
	while (s[j])
	{
		if ((s[j] == '"' || s[j] == '\'') && *c == 0)
			j = handle_quotes(s, c, &j);
		else if (s[j] == 32 && *c == 0)
			break ;
		if (s[j])
			j++;
	}
	if (s[j] == 32)
		*i = j + 1;
	else
		*i = j;
	return (ft_strndup(s + start, j - start));
}

char	**split_in_valid_spaces(char *s)
{
	int		i;
	int		k;
	int		nb;
	char	c;
	char	**ret;

	nb = nb_of_word_for_valid_spaces(s);
	ret = malloc(sizeof(char *) * (nb + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	i = 0;
	c = 0;
	k = 0;
	while (s[i])
	{
		ret[k] = find_next_word(s, &i, &c);
		k++;
	}
	ret[k] = NULL;
	return (ret);
}
