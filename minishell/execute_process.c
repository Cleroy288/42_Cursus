/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:46:04 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:31:13 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_one_command_only(void)
{
	int		i;
	pid_t	pid;

	i = 0;
	if (handle_errors(i) == -1)
		return ;
	pid = fork();
	if (pid < 0)
		printf("error fork\n");
	else if (pid == 0)
	{
		handle_child_process(i);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &g_data.status, 0);
		ft_signal_handler_child();
	}
}

void	ft_initialize_pipes(void)
{
	int	i;

	i = 0;
	while (i != g_data.commands_count)
	{
		ft_pipe(i);
		i++;
	}
}

void	ft_handle_child_process(int i)
{
	g_data.status = 2;
	signal(SIGQUIT, SIG_DFL);
	ft_signal_handler_child();
	ft_child(i);
	ft_child_process(i);
	exit(0);
}

void	ft_free_command(int nb)
{
	int	i;

	i = 0;
	if (!g_data.commands[nb])
		return ;
	while (g_data.commands[nb][i])
	{
		free(g_data.commands[nb][i]);
		g_data.commands[nb][i] = NULL;
		i++;
	}
	free(g_data.commands[nb]);
	g_data.commands[nb] = NULL;
}

void	ft_execute_processes(void)
{
	int	i;

	i = 0;
	while (i != g_data.commands_count)
	{
		ft_fork(i);
		if (g_data.pids[i] == 0)
			ft_handle_child_process(i);
		else
			ft_parent(i);
		ft_free_command(i);
		i++;
	}
}
