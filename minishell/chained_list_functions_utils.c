/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_functions_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:15:56 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:32:51 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_add_shell(t_list_shell *list, int value)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	new_node->value = value;
	new_node->next = NULL;
	if (list->tail == NULL)
	{
		new_node->prev = NULL;
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		new_node->prev = list->tail;
		list->tail->next = new_node;
		list->tail = new_node;
	}
}

void	list_free_shell(t_list_shell *list)
{
	t_node	*current_node;
	t_node	*next_node;

	current_node = list->head;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	list->head = NULL;
	list->tail = NULL;
}

void	ft_lstadd_back_shell(t_list_shell *lst, t_node *new)
{
	if (!lst || !new)
		return ;
	if (!lst->tail)
	{
		lst->head = new;
		lst->tail = new;
	}
	else
	{
		lst->tail->next = new;
		new->prev = lst->tail;
		lst->tail = new;
	}
}
