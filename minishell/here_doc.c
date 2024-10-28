/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:48:19 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 16:50:21 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_for_processes(void)
{
	int	i;

	i = 0;
	while (i != g_data.commands_count)
	{
		waitpid(g_data.pids[i], NULL, 0);
		i++;
	}
}

void	ft_init_and_execute_process(void)
{
	if (g_data.commands_count == 1)
		return (ft_one_command_only());
	ft_initialize_pipes();
	ft_execute_processes();
	ft_wait_for_processes();
}

char	*ft_set_variables_in_here_doc(char *line_to_here_doc)
{
	char	*temp;

	temp = ft_set_variables_in_place(line_to_here_doc);
	line_to_here_doc = ft_strdup(temp);
	free(temp);
	return (line_to_here_doc);
}

int	ft_fulfilling(int fd_here_doc)
{
	char	*line_to_here_doc;

	while (1)
	{
		line_to_here_doc = readline("here_doc >");
		if (g_data.signal_here_doc == 1)
			return (1);
		if (!line_to_here_doc)
			break ;
		line_to_here_doc = ft_set_variables_in_here_doc(line_to_here_doc);
		g_data.status = 3;
		if ((line_to_here_doc[0] != '\0'
				&& ft_strncmp(line_to_here_doc, g_data.word_here_doc,
					ft_strlen(line_to_here_doc)) == 0)
			|| g_data.signal_here_doc == 1)
		{
			free(line_to_here_doc);
			close(fd_here_doc);
			return (1);
		}
		ft_putstr_fd(line_to_here_doc, fd_here_doc);
		ft_putstr_fd("\n", fd_here_doc);
		free(line_to_here_doc);
	}
	return (0);
}

void	ft_here_doc_fulfilling(void)
{
	int		fd_here_doc;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_signal_handler_here_doc();
	if (g_data.signal_here_doc == 1)
		return ;
	if (g_data.here_doc && g_data.word_here_doc)
	{
		fd_here_doc = open(g_data.here_doc, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		while (1)
		{
			if (ft_fulfilling(fd_here_doc) == 1)
			{
				g_data.signal_here_doc = 0;
				return ;
			}
		}
		close(fd_here_doc);
		g_data.input_file = g_data.here_doc;
	}
}
