/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:30:54 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:26:14 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_until_letter(int *i, int *occurrences, char *str, char letter)
{
	while (str[(*i)])
	{
		if (str[(*i)] == letter)
			(*occurrences)++;
		(*i)++;
	}
}

int	check_and_skip(char *str, char *take_out, int i)
{
	int		j;

	j = 0;
	while (str[i + j] == take_out[j] && str[i + j])
		j++;
	if (j == (int)ft_strlen(take_out))
		return (j);
	return (0);
}

char	*ft_str_without_w(char *str, char *take_out)
{
	int		i;
	int		k;
	int		skip;
	char	*new;

	i = 0;
	k = 0;
	if (!str)
		return (NULL);
	if (!take_out)
		return (str);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		exit(EXIT_FAILURE);
	while (str[i])
	{
		skip = check_and_skip(str, take_out, i);
		if (skip)
			i += skip;
		else
			new[k++] = str[i++];
	}
	new[k] = '\0';
	return (new);
}

char	*ft_str_without_w_free_str(char *str, char *take_out)
{
	int		i;
	int		k;
	int		skip;
	char	*new;

	i = 0;
	k = 0;
	if (!str)
		return (NULL);
	if (!take_out)
		return (str);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		exit(EXIT_FAILURE);
	while (str[i])
	{
		skip = check_and_skip(str, take_out, i);
		if (skip)
			i += skip;
		else
			new[k++] = str[i++];
	}
	new[k] = '\0';
	free(str);
	return (new);
}
