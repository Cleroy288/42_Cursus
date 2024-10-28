/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:36:29 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:36:44 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_on_char(char c, char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	skip_special_word(char *s, size_t *i, int *nb)
{
	char	c;

	c = s[*i];
	(*i)++;
	(*nb)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
	if (s[*i])
		(*i)++;
}

void	skip_normal_word(char *s, size_t *i, char *sp, int *nb)
{
	(*nb)++;
	while (s[*i] && s[*i] != ' ' && !ft_is_on_char(s[*i], sp))
		(*i)++;
}

int	ft_nb_of_words(char *s, char *sp)
{
	int		nb;
	size_t	i;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (ft_is_on_char(s[i], sp))
			skip_special_word(s, &i, &nb);
		else
			skip_normal_word(s, &i, sp, &nb);
		while (s[i] == ' ')
			i++;
	}
	return (nb);
}

char	*ft_return_value(int end, int start, char *s)
{
	char	*word;

	word = (char *)malloc(end - start + 1);
	if (!word)
		exit(EXIT_FAILURE);
	ft_strncpy(word, &s[start], end - start);
	if (!word)
		return (s);
	word[end - start] = '\0';
	return (word);
}
