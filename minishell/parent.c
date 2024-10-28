/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:29:27 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/12 17:40:20 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parent(int pos)
{
	if (pos < g_data.commands_count - 1)
		close(g_data.pipefds[pos][1]);
	if (pos > 0)
		close(g_data.pipefds[pos - 1][0]);
}
