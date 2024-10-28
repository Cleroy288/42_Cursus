/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_what_u_give_me.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:35:16 by chleroy           #+#    #+#             */
/*   Updated: 2023/06/05 11:35:23 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_what_u_give_me(t_pipex *st, int one_for_cmmargs, int one_pids)
{
	int		i;

	i = 0;
	if (one_for_cmmargs == 1)
	{
		while (st->cmd_args[i])
		{
			free(st->cmd_args[i]);
			i++;
		}
		free(st->cmd_args);
	}
	if (one_pids == 1)
	{
		free(st->pids);
	}
}
