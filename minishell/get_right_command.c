/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_right_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:01:59 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 18:02:51 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quotes(char *s, int i, int *j)
{
	if (s[i] && s[i] == 39)
	{
		while (s[i + (*j)] && s[i + (*j)] != 39)
			(*j)++;
		return (1);
	}
	return (0);
}

char	*ft_extra_arg_in_single(char *s)
{
	int		i;
	int		j;
	char	*ret;

	i = -1;
	j = 0;
	if (ft_go_to_quotes(s) == 1)
		return (s);
	while (s[++i])
	{
		if (ft_quotes(s, i, &j) == 1)
			break ;
	}
	ret = malloc(sizeof(char) * (j + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	j = 0;
	while (s[i + j] && s[i + j] != 39)
	{
		ret[j] = s[i + j];
		j ++;
	}
	ret[j] = '\0';
	return (ret);
}

void	ft_right_command_quotes(char *quotes, int *i, char *str)
{
	if ((*quotes) == 0)
		(*quotes) = str[(*i)];
	else if ((*quotes) == str[(*i)])
		(*quotes) = 0;
	(*i)++;
}

char	*ft_go_get_right_command_part_2(int *i, char *str, char *quotes)
{
	int		j;
	char	*ret;

	while (str[(*i)] && (str[(*i)] == '|' || str[(*i)] == ' '))
		(*i)++;
	j = (*i);
	while (str[j] && (str[j] != '|' || (*quotes) != 0))
	{
		if (str[j] == '"' || str[j] == '\'')
		{
			if ((*quotes) == 0)
				(*quotes) = str[j];
			else if ((*quotes) == str[j])
				(*quotes) = 0;
		}
		if (str[j] && ((str[j] == '>' || str[j] == '<') && *quotes == 0))
		{
			ret = ft_substr(str, (*i), j - (*i));
			return (ret);
		}
		j++;
	}
	ret = ft_substr(str, (*i), j - (*i));
	return (ret);
}

char	*go_get_right_command(char *str, int nb_command)
{
	int		i;
	int		nb;
	char	*ret;
	char	quotes;

	if (!str)
		return (NULL);
	quotes = 0;
	nb = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			ft_right_command_quotes(&quotes, &i, str);
		if (quotes == 0 && str[i] == '|')
			nb++;
		if (nb == nb_command)
		{
			ret = ft_go_get_right_command_part_2(&i, str, &quotes);
			if (!ret)
				return (NULL);
			return (ret);
		}
	}
	return (NULL);
}
