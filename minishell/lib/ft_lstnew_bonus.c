/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:04:33 by chleroy           #+#    #+#             */
/*   Updated: 2023/06/28 16:50:00 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*link;

	if (!content)
		return (NULL);
	link = malloc(sizeof(t_list));
	if (!link)
		return (NULL);
	if (link)
	{
		link->content = content;
		link->next = 0;
	}
	return (link);
}
