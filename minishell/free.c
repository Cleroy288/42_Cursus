/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:24:06 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/15 15:44:44 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_memory_stack(void)
{
	int		index;

	index = 0;
	while (index < g_data.index_in_mem_stack)
	{
		free(g_data.stack_withe_mem_address[index]);
		index ++;
	}
}

void	ft_free_double_pointer(char **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	if (ptr)
		free(ptr);
	ptr = NULL;
}
