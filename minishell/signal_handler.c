/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:55:34 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 16:36:32 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_handler_default(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &reset_prompt);
}

void	ft_signal_handler_parent(void)
{
	if (WIFEXITED(g_data.status))
		g_data.return_value = WEXITSTATUS(g_data.status);
	if (WIFSIGNALED(g_data.status))
	{
		g_data.return_value = WIFEXITED(g_data.status);
		if (g_data.return_value == 2)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	ft_signal_handler_child(void)
{
	if (WIFEXITED(g_data.status))
		g_data.return_value = WEXITSTATUS(g_data.status);
	if (WIFSIGNALED(g_data.status))
	{
		g_data.return_value = WIFEXITED(g_data.status);
		if (g_data.return_value == 2)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_data.return_value == 3)
		{
			ft_putendl_fd("^\\Quit: 3", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

static void	set_signal_here_doc(int sig)
{
	(void)sig;
	g_data.signal_here_doc = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal_handler_here_doc(void)
{
	signal(SIGINT, &set_signal_here_doc);
	signal(SIGQUIT, SIG_IGN);
}
