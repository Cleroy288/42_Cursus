/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:30:16 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/17 21:41:51 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(void)
{
	g_data.infile_fd = STDIN_FILENO;
	g_data.outfile_fd = STDOUT_FILENO;
	ft_here_doc_fulfilling();
}

void	ft_principal_pipex_function(void)
{
	int	fd;

	ft_init();
	if (g_data.input_file || g_data.here_doc)
	{
		if (g_data.here_doc && g_data.word_here_doc)
			g_data.input_file = ft_strdup(g_data.here_doc);
		fd = open(g_data.input_file, O_RDONLY);
		if (fd == -1 && ft_strncmp(g_data.commands[0][0], "cat", 3) != 0)
			perror("error open infile");
		g_data.infile_fd = fd;
	}
	if (g_data.output_file)
	{
		fd = 0;
		if (g_data.append_is_one == 1)
			fd = open(g_data.output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (g_data.append_is_one == 0)
			fd = open(g_data.output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			perror("error open outfile");
		g_data.outfile_fd = fd;
	}
	ft_init_and_execute_process();
	ft_is_command_cd();
}

void	ft_pipe(int pos)
{
	int	stat;

	stat = pipe(g_data.pipefds[pos]);
	if (stat == -1)
		perror("pipe");
}

void	ft_fork(int pos)
{
	g_data.pids[pos] = fork();
	if (g_data.pids[pos] == -1)
		perror("fork");
}
