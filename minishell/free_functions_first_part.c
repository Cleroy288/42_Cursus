/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_first_part.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:21:42 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:26:03 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_outputfile(void)
{
	if (g_data.output_file != NULL)
	{
		free(g_data.output_file);
		g_data.output_file = NULL;
	}
}

void	ft_free_inputfile(void)
{
	if (g_data.input_file != NULL)
	{
		free(g_data.input_file);
		g_data.input_file = NULL;
	}
}

void	ft_free_here_doc_word(void)
{
	if (g_data.word_here_doc != NULL)
	{
		free(g_data.word_here_doc);
		g_data.word_here_doc = NULL;
	}
}

void	ft_free_initial_command(void)
{
	if (g_data.initial_command != NULL)
	{
		free(g_data.initial_command);
		g_data.initial_command = NULL;
	}
}

void	ft_free_return_from_rdl(void)
{
	if (g_data.return_str_from_rdl != NULL)
	{
		free(g_data.return_str_from_rdl);
		g_data.return_str_from_rdl = NULL;
	}
}
