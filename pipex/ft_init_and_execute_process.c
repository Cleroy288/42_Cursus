/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_and_execute_process.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:35:38 by chleroy           #+#    #+#             */
/*   Updated: 2023/06/05 11:39:02 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	ft_close_pipes(t_pipex *st, int n)
{
	while (--n && st->pipefds[n])
	{
		close(st->pipefds[n][0]);
		close(st->pipefds[n][1]);
	}
}

static	void	ft_one_command_only(t_pipex *st)
{
	int	i;

	i = 0;
	ft_dup2(st->outfile_fd, STDOUT_FILENO, st);
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
	ft_close(&st->outfile_fd, st);
	ft_close(&st->infile_fd, st);
}

static	void	ft_pipe(t_pipex *st, int pos)
{
	int	stat;

	stat = pipe(st->pipefds[pos]);
	if (stat == -1)
	{
		ft_putstr_fd("error pipe cmd_args", 1);
		ft_free_what_u_give_me(st, 1, 1);
		exit(EXIT_FAILURE);
	}
}

static	void	ft_fork(t_pipex *st, int pos)
{
	st->pids[pos] = fork();
	if (st->pids[pos] == -1)
	{
		ft_putstr_fd("error fork\n", 1);
		ft_free_what_u_give_me(st, 1, 1);
		exit(EXIT_FAILURE);
	}
}

void	ft_init_and_execute_process(t_pipex *st)
{
	int	i;

	i = 0;
	st->pids = malloc(sizeof(pid_t) * (st->cmd_args_count + 1));
	if (!st->pids)
		exit(EXIT_FAILURE);
	if (st->cmd_args_count == 1)
		return (ft_one_command_only(st));
	while (i < st->cmd_args_count)
	{
		ft_pipe(st, i);
		ft_fork(st, i);
		if (st->pids[i] == 0)
			ft_child_process(st, i);
		ft_close_parent(i, st);
		i++;
	}
	ft_close_pipes(st, st->cmd_args_count);
	i = 0;
	while (i < st->cmd_args_count)
	{
		waitpid(st->pids[i], NULL, 0);
		i++;
	}
}
