/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:33:32 by chleroy           #+#    #+#             */
/*   Updated: 2023/06/05 11:34:35 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_child(t_pipex *st, int pos)
{
	ft_dup2(st->infile_fd, STDIN_FILENO, st);
	ft_close(&st->infile_fd, st);
	ft_dup2(st->pipefds[pos][1], STDOUT_FILENO, st);
	ft_close(&st->pipefds[pos][1], st);
}

void	ft_last_child(int pos, t_pipex *st)
{
	ft_dup2(st->pipefds[pos - 1][0], STDIN_FILENO, st);
	ft_close(&st->pipefds[pos - 1][0], st);
	ft_dup2(st->outfile_fd, STDOUT_FILENO, st);
	ft_close(&st->outfile_fd, st);
}

void	ft_middel_child(int pos, t_pipex *st)
{
	ft_dup2(st->pipefds[pos - 1][0], STDIN_FILENO, st);
	ft_close(&st->pipefds[pos - 1][0], st);
	ft_dup2(st->pipefds[pos][1], STDOUT_FILENO, st);
	ft_close(&st->pipefds[pos][1], st);
}

void	ft_child(int pos, t_pipex *st)
{
	ft_close_children(st, pos);
	if (pos == 0)
		ft_first_child(st, pos);
	else if (pos == st->cmd_args_count - 1)
		ft_last_child(pos, st);
	else
		ft_middel_child(pos, st);
}

void	ft_child_process(t_pipex *st, int i)
{
	ft_child(i, st);
	st->path = NULL;
	st->path = ft_get_path(st, i);
	if (access(st->path, X_OK | F_OK) != 0)
	{
		ft_putstr_fd("error path access\n", 2);
		exit(EXIT_FAILURE);
	}
	if (execve(st->path, st->cmd_args[i], st->env) == -1)
	{
		fprintf(stderr, "Failed to execute command: %s\n", st->cmd_args[i][0]);
		exit(EXIT_FAILURE);
	}
}
