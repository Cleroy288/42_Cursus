/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variable_in_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:58:06 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 18:11:50 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calculate_result_length(char *string, char *word)
{
	int	length;
	int	i;
	int	count;

	length = 0;
	i = 0;
	count = 0;
	while (string[i])
	{
		if (string[i] == '$')
		{
			count++;
			while (string[i] && string[i] != ' ')
				i++;
			length += ft_strlen(word);
		}
		else
		{
			length++;
			i++;
		}
	}
	length += length + (count * 30);
	return (length);
}

char	*ft_skip_and_cpy(char *str, char *word, int *nb)
{
	int		i[2];
	char	*result;

	result = NULL;
	i[0] = 0;
	i[1] = 0;
	(*nb) = 0;
	if (str[(*nb)] && (((*nb) == 0 && str[(*nb)] == '$') || (str[(*nb)] == '$'
				&& i[1] == 0 && str[(*nb) - 1] != 39 && (*nb) != 0)))
	{
		while (str[(*nb)] && str[(*nb)] != ' ' && str[(*nb)] != 39)
			(*nb)++;
		if (str[(*nb)] == '"')
			(*nb)++;
		while (word[i[1]])
			result[i[0]++] = word[i[1]++];
	}
	else
	{
		if (str[(*nb)] && str[(*nb)] == '"')
			(*nb)++;
		if (str[(*nb)] && result[i[0]])
			result[i[0]++] = str[(*nb)++];
	}
	return (result);
}

char	*ft_set_variable_in_str(char *s1, char *word, char *s2)
{
	int		total_len;
	char	*result;
	int		i;

	i = 0;
	if (!s1)
		s1 = s2;
	if (!word)
		return (NULL);
	total_len = calculate_result_length(s1, word);
	result = malloc(sizeof(char) * (total_len + 50));
	if (!result)
		exit(EXIT_FAILURE);
	while (s1[i] && i < (int)ft_strlen(s1))
		result = ft_skip_and_cpy(s1, word, &i);
	result[i] = 0;
	return (result);
}

char	*ft_last_operation_remove_single_quotes(char *s)
{
	int		i[0];
	int		j;
	char	*nvx;

	i[0] = 0;
	j = -1;
	i[1] = 0;
	nvx = malloc(sizeof(char) * (ft_strlen(s) + 50));
	if (!nvx || !s)
		exit(EXIT_FAILURE);
	while (s[i[0]])
	{
		if (s[i[0]] == 39 && s[i[0] + 1] == '$' && i[0]++)
			i[1] = 1;
		else if (s[i[0]] == 39 && i[1] == 1 && i[0]++)
			i[1] = 0;
		else
		{
			if (s[i[0]])
				nvx[++j] = s[i[0]++];
		}
	}
	nvx[j] = '\0';
	free(s);
	return (nvx);
}

char	*ft_is_dollars_sec_part(char **val, char **var, char *ret, char *s)
{
	(*val) = ft_find_in_env((*var));
	if (ft_strncmp((*val), "-R", 2) == 0)
		(*val) = ft_strdup("this variable DOES NOT EXIST!");
	free((*var));
	ret = ft_set_variable_in_str(ret, (*val), s);
	if (!ret)
		return (NULL);
	free((*val));
	(*val) = NULL;
	(*var) = NULL;
	return (ret);
}
