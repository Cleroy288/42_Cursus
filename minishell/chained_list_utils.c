/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:17:39 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:18:07 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_env(t_env *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

char	*ft_strldup(char *s, int len)
{
	char	*s2;
	int		i;

	i = 0;
	if (!s)
		return (0);
	s2 = malloc((sizeof(char) * (len + 1)));
	if (!s2)
		exit(EXIT_FAILURE);
	while (s[i] && i < len)
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

void	ft_set_value(char *key, char *value, t_env **lst)
{
	(*lst)->key = key;
	(*lst)->value = value;
	(*lst)->next = NULL;
}
