/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:29:03 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 10:26:55 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child(int pos)
{
	int	i;

	if (pos == 0)
	{
		dup2(g_data.infile_fd, STDIN_FILENO);
		dup2(g_data.pipefds[pos][1], STDOUT_FILENO);
	}
	else if (pos == g_data.commands_count - 1)
	{
		dup2(g_data.pipefds[pos - 1][0], STDIN_FILENO);
		dup2(g_data.outfile_fd, STDOUT_FILENO);
	}
	else
	{
		dup2(g_data.pipefds[pos - 1][0], STDIN_FILENO);
		dup2(g_data.pipefds[pos][1], STDOUT_FILENO);
	}
	i = 0;
	while (i != g_data.commands_count)
	{
		close(g_data.pipefds[i][0]);
		close(g_data.pipefds[i][1]);
		i++;
	}
}

void	ft_exit_child_process(void)
{
	if (g_data.path == NULL)
	{
		perror("path");
		exit(EXIT_FAILURE);
	}
	if (access(g_data.path, X_OK | F_OK) != 0)
	{
		exit(EXIT_FAILURE);
	}
}

void	ft_child_process(int i)
{
	int	j;
	int	k;

	ft_child(i);
	g_data.status = 2;
	if (ft_builtin(i) == 1)
		return ;
	g_data.path = NULL;
	g_data.path = ft_get_path(i, 0);
	ft_exit_child_process();
	k = -1;
	while (g_data.commands[++k])
	{
		j = 0;
		while (g_data.commands[k][j])
			j++;
	}
	g_data.status = 2;
	ft_signal_handler_child();
	signal(SIGQUIT, SIG_DFL);
	if (execve(g_data.path, g_data.commands[i], g_data.env) == -1)
	{
		perror("error execve");
		exit(EXIT_FAILURE);
	}
}
