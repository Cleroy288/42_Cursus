/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_first_part.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:11:11 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:13:14 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_outputfile(void)
{
	if (g_data.output_file)
		g_data.output_file = NULL;
}

void	ft_init_inputfile(void)
{
	if (g_data.input_file)
		g_data.input_file = NULL;
}

void	ft_init_here_doc_word(void)
{
	if (g_data.word_here_doc)
		g_data.word_here_doc = NULL;
}

void	ft_init_initial_command(void)
{
	if (g_data.initial_command)
		g_data.initial_command = NULL;
}

void	ft_init_return_from_rdl(void)
{
	if (g_data.return_str_from_rdl)
		g_data.return_str_from_rdl = NULL;
}
