/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_and_dispach.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:05:48 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:10:16 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_char_in_str(char *s, char c, char c2)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c || s[i] == c2)
			return (1);
		i ++;
	}
	return (0);
}

void	ft_process_and_dispatch(char *ret)
{
	g_data.initial_command = ret;
	ft_set_spaces_in_command();
	if (ft_process_the_input_validity_quotes(ret) == 0)
	{
		ft_extract_input_output_file(g_data.initial_command);
		ft_create_command_with_no_in_out_file_or_redirections();
		ft_extract_commands_and_options();
		ft_principal_pipex_function();
		if (g_data.here_doc != NULL && g_data.word_here_doc != NULL)
		{
			if (unlink(g_data.here_doc) != 0)
				perror("Failed to delete the file");
		}
	}
	else
		return ;
}

void	ft_first_singal_handler(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_signal_handler_default();
	stifle_history(500);
}

void	ft_sec_signal_handler(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_init_struct();
	ft_signal_handler_default();
}

void	ft_free_in_main_process(void)
{
	int	i;

	i = 0;
	ft_free_function();
	free(g_data.initial_command);
	free(g_data.treated_command);
	while (i < g_data.commands_count)
	{
		free(g_data.commands[i]);
		g_data.commands[i] = NULL;
		i++;
	}
}
