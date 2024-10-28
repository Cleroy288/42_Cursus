/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chained_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:09:20 by chleroy           #+#    #+#             */
/*   Updated: 2023/09/19 17:18:47 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env(char *content, char *str)
{
	t_env	*lst;
	char	*key;
	char	*value;
	int		i;

	lst = malloc(sizeof(t_env));
	if (!lst)
		exit(EXIT_FAILURE);
	i = 0;
	if (!content)
	{
		ft_set_value(NULL, NULL, &lst);
		return (lst);
	}
	while (content[i] && content[i] != '=')
		i++;
	key = ft_strldup(content, i);
	if (!str)
		value = ft_strdup(content + i + 1);
	else
		value = ft_strdup(str);
	ft_set_value(key, value, &lst);
	return (lst);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstclear_env(t_env *lst)
{
	t_env	*temp;

	if (!lst)
		return ;
	while (lst)
	{
		temp = lst;
		lst = lst->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!lst)
		return ;
	temp = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
