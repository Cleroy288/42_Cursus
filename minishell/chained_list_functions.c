/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:16:32 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:16:15 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_front_shell(t_list_shell *lst, t_node *new)
{
	if (!lst || !new)
		return ;
	if (!lst->head)
	{
		lst->head = new;
		lst->tail = new;
	}
	else
	{
		lst->head->prev = new;
		new->next = lst->head;
		lst->head = new;
	}
}

void	ft_lstclear_shell(t_list_shell *lst)
{
	t_node	*tmp;

	if (!lst)
		return ;
	while (lst->head)
	{
		tmp = lst->head;
		lst->head = lst->head->next;
		free(tmp);
	}
	lst->tail = NULL;
}

void	ft_lstdelone_shell(t_list_shell *lst, t_node *node)
{
	if (!lst || !node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (lst->head == node)
		lst->head = node->next;
	if (lst->tail == node)
		lst->tail = node->prev;
	free(node);
}

t_node	*ft_lstnew_shell(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		exit(EXIT_FAILURE);
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	ft_lstsize_shell(t_list_shell *lst)
{
	int		size;
	t_node	*node;

	if (!lst)
		return (0);
	size = 0;
	node = lst->head;
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
}
