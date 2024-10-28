/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:50:23 by chleroy           #+#    #+#             */
/*   Updated: 2023/09/19 17:14:44 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_path_splitted(void)
{
	g_data.path_splitted = NULL;
}

void	ft_init_path(void)
{
	if (g_data.path)
		g_data.path = NULL;
}

void	ft_init_commands(void)
{
	int	i;

	i = 0;
	while (g_data.commands[i] != NULL)
	{
		g_data.commands[i] = NULL;
		i++;
	}
}

void	ft_init_treated(void)
{
	if (g_data.treated_command)
		g_data.treated_command = NULL;
}

int	ft_init_struct(void)
{
	if (g_data.input_file)
		ft_init_inputfile();
	if (g_data.output_file)
		ft_init_outputfile();
	if (g_data.here_doc)
		g_data.here_doc = NULL;
	if (g_data.word_here_doc)
		ft_init_here_doc_word();
	if (g_data.append_is_one == 1)
		g_data.append_is_one = 0;
	if (g_data.initial_command)
		ft_init_initial_command();
	if (g_data.return_str_from_rdl)
		ft_init_return_from_rdl();
	if (g_data.command_in_pipes)
		ft_init_command_splitted_in_pipes();
	if (g_data.path_splitted)
		ft_init_path_splitted();
	if (g_data.path)
		ft_init_path();
	ft_init_commands();
	if (g_data.treated_command)
		ft_init_treated();
	g_data.signal_here_doc = 0;
	return (1);
}
