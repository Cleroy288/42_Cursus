/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:42:57 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/20 12:57:12 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_errors(int i)
{
	if (!g_data.commands[i][0])
	{
		printf("Error: input\n");
		return (-1);
	}
	if (ft_strncmp(g_data.commands[i][0], "export", 6) == 0
		&& ft_builtin(0) == 1)
		return (-1);
	if (g_data.commands[i][0]
		&& ft_strncmp(g_data.commands[i][0], "unset", 5) == 0
		&& ft_builtin(0) == 1)
		return (-1);
	return (1);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_dup_close(void)
{
	if (g_data.infile_fd != STDIN_FILENO)
		ft_dup2(g_data.infile_fd, STDIN_FILENO);
	if (g_data.outfile_fd != STDOUT_FILENO)
		ft_dup2(g_data.outfile_fd, STDOUT_FILENO);
	if (g_data.outfile_fd != STDOUT_FILENO)
		ft_close(&g_data.outfile_fd);
	if (g_data.infile_fd != STDIN_FILENO)
		ft_close(&g_data.infile_fd);
}

void	exec_command(int i)
{
	if ((ft_strncmp(g_data.commands[i][0], "cd", 2) == 0)
		|| (ft_strncmp(g_data.commands[i][0], "OLDPWD", 6) == 0))
		return ;
	if (ft_strncmp(g_data.commands[i][0], "./", 2) == 0
		&& execve(g_data.commands[i][0], g_data.commands[i], g_data.env) == -1)
	{
		ft_putstr_fd(g_data.commands[i][0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (execve(g_data.path, g_data.commands[i], g_data.env) == -1)
	{
		ft_putstr_fd(g_data.commands[i][0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void	handle_child_process(int i)
{
	reset_signals();
	handle_dup_close();
	if (ft_builtin(0) == 1)
		exit (EXIT_SUCCESS);
	g_data.path = ft_get_path(i, 0);
	exec_command(i);
	exit(EXIT_SUCCESS);
}
