/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:54:09 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/08 15:39:34 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nb_word(const char *s, char c)
{
	int		in_w;
	size_t	nb;

	in_w = 0;
	nb = 0;
	while (*s)
	{
		if (*s == c)
			in_w = 0;
		else if (in_w == 0)
		{
			in_w = 1;
			nb++;
		}
		s++;
	}
	return (nb);
}

static	char	*ft_get_word(const char *s, char c)
{
	size_t	len;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_memcpy(word, s, len);
	word[len] = '\0';
	return (word);
}

static	void	ft_free_split(char **str, size_t nb_w)
{
	size_t	i;

	i = 0;
	while (i != nb_w)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static char	**ft_write_line(const char *s, char c, char **str, int pos)
{
	size_t	pos_tab;

	pos_tab = -1;
	while (s[pos])
	{
		if (s[pos] != c)
		{
			str[++pos_tab] = ft_get_word(s + pos, c);
			if (!str[pos_tab])
			{
				ft_free_split(str, pos_tab);
				return (NULL);
			}
			while (s[pos] && s[pos] != c)
				pos++;
		}
		else
			pos++;
	}
	str[++pos_tab] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**str;

	i = 0;
	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (ft_nb_word(s, c) + 1));
	if (!str)
		return (NULL);
	str = ft_write_line(s, c, str, i);
	if (!str)
	{
		free(str);
		return (NULL);
	}
	return (str);
}
