/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arg_for_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:25:32 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/20 12:32:49 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_or_interpolate(t_sub_var *quotes)
{
	if (quotes->s[(*quotes).i] == '\'')
		(*quotes).in_single_quotes = !(*quotes).in_single_quotes;
	if (quotes->s[(*quotes).i] == '"')
		(*quotes).in_double_quotes = !(*quotes).in_double_quotes;
	if (quotes->s[(*quotes).i] == '$' && (!(*quotes).in_single_quotes
			|| (*quotes).in_double_quotes)
		&& (quotes->s[(*quotes).i + 1] != '?'))
	{
		(*quotes).arg = get_env_var_name(quotes->s, &quotes->i);
		(*quotes).value = ft_find_argument_in_env_value((*quotes).arg);
		append_value_or_var((*quotes).new_str, &quotes->j,
			(*quotes).value, (*quotes).i - ft_strlen((*quotes).arg) - 1);
		free((*quotes).arg);
	}
	else
		((*quotes).new_str)[(*quotes).j++] = quotes->s[(*quotes).i++];
}

char	*ft_set_variables_in_place(char *s)
{
	t_sub_var	quotes;

	if (!s)
		return (NULL);
	quotes.s = ft_strdup(s);
	ft_init_t_quotes(&quotes);
	quotes.new_str = malloc(sizeof(char) * (ft_len_new_str(s) + 1));
	if (!quotes.new_str)
		exit(EXIT_FAILURE);
	while (quotes.s[quotes.i])
		copy_or_interpolate(&quotes);
	quotes.new_str[quotes.j] = '\0';
	free(quotes.s);
	free(s);
	return (quotes.new_str);
}

void	ft_copy_to_return(char **tab, char **ret, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			(*ret)[k] = tab[i][j];
			j++;
			k++;
		}
		if (tab[i] && tab[i + 1] && tab[i][j] == '\0')
		{
			(*ret)[k] = c;
			k++;
		}
		i++;
	}
	(*ret)[k] = '\0';
	return ;
}

char	*ft_join_2d_tab_and_set_char(char **tab, int one_to_free_tab, char c)
{
	int		i;
	int		len;
	char	*ret;

	len = 0;
	i = 0;
	while (tab[i])
	{
		len += ft_strlen(tab[i]) + 1;
		i ++;
	}
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	ft_copy_to_return(tab, &ret, c);
	if (one_to_free_tab == 1)
		ft_free_double_pointer(tab);
	return (ret);
}

char	*ft_magic(char *str)
{
	char	*s;
	char	**splitted;
	char	*new;

	s = str;
	splitted = ft_special_split(s, " '\"");
	new = ft_join_2d_tab_and_set_char(splitted, 1, 32);
	return (new);
}
