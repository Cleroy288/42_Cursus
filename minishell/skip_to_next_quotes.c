/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_to_next_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:58:02 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 16:58:51 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_go_at_next_quotes(char *s, int index, char *c)
{
	if (!s || !c)
		return (index);
	index++;
	while (s[index] && s[index] != *c)
		index++;
	if (s[index] == *c)
		*c = 0;
	return (index);
}

int	ft_nb_of_command(char *s)
{
	int		i;
	int		len;
	int		count;
	char	quote;

	i = 0;
	count = 1;
	quote = 0;
	if (!s || s[0] == '\0')
		return (0);
	len = ft_strlen(s);
	while (s[i] && i < len)
	{
		if ((s[i] == 39 || s[i] == '"') && quote == 0)
		{
			quote = s[i];
			i = ft_go_at_next_quotes(s, i, &quote);
		}
		else if (s[i] == '|' && quote == 0)
			count++;
		if (s[i])
			i++;
	}
	return (count);
}

int	ft_skipping(char *s, int j_index, char *c)
{
	*c = s[j_index];
	j_index++;
	while (s[j_index] && s[j_index] != *c)
		j_index++;
	if (s[j_index] && s[j_index] == *c)
		*c = 0;
	return (j_index);
}

char	*ft_last_pass(char *s, int *index_i, int *index_j)
{
	char	*ret;

	ret = ft_strndup(s + *index_i, *index_j - *index_i);
	if (!ret)
		return (NULL);
	if (s[*index_j] == '|')
		(*index_j)++;
	*index_i = *index_j;
	return (ret);
}

int	update_j_index(char *s, int *j_index, char *c)
{
	*j_index = *j_index;
	while (s[*j_index])
	{
		if ((s[*j_index] == '"' || s[*j_index] == '\'') && *c == 0)
			*j_index = ft_skipping(s, *j_index, c);
		else if (s[*j_index] == '|' && *c == 0)
			break ;
		if (s[*j_index])
			(*j_index)++;
	}
	return (*j_index);
}
