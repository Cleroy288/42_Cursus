/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:04:33 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/24 22:37:49 by charleslero      ###   ########.fr       */
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
