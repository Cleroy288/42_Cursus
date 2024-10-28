/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:11:16 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:23:51 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_function(void)
{
	if (g_data.input_file != NULL)
		ft_free_inputfile();
	if (g_data.output_file != NULL)
		ft_free_outputfile();
	if (g_data.here_doc)
		g_data.here_doc = NULL;
	if (g_data.word_here_doc != NULL)
		ft_free_here_doc_word();
	if (g_data.append_is_one == 1)
		g_data.append_is_one = 0;
	if (g_data.initial_command != NULL)
		ft_free_initial_command();
	if (g_data.return_str_from_rdl != NULL)
		ft_free_return_from_rdl();
	if (g_data.path_splitted != NULL)
		ft_free_path_splitted();
	if (g_data.path != NULL)
		ft_free_path();
	if (g_data.commands[0] != NULL)
		ft_free_commands();
	if (g_data.treated_command != NULL)
		ft_free_treated_command();
	return (1);
}
