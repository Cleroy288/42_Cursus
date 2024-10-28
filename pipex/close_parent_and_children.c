/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_parent_and_children.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:32:27 by chleroy           #+#    #+#             */
/*   Updated: 2023/06/05 11:33:11 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_children(t_pipex *st, int pos)
{
	if (pos == 0)
	{
		ft_close(&st->pipefds[0][0], st);
		ft_close(&st->outfile_fd, st);
	}
	else if (pos == st->cmd_args_count - 1)
	{
		return ;
	}
	else
	{
		ft_close(&st->infile_fd, st);
		ft_close(&st->outfile_fd, st);
	}
}

void	ft_close_parent(int pos, t_pipex *st)
{
	if (pos == 0)
	{
		ft_close(&st->infile_fd, st);
		ft_close(&st->pipefds[0][1], st);
	}
	else if (pos == st->cmd_args_count - 1)
	{
		ft_close(&st->pipefds[pos - 1][0], st);
		ft_close(&st->outfile_fd, st);
	}
	else
	{
		ft_close(&st->pipefds[pos - 1][0], st);
		ft_close(&st->pipefds[pos][1], st);
	}
}
