/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_input_outputfile.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:00:06 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:32:26 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_tmp(char *src)
{
	char	*tmp;

	tmp = ft_strdup(src);
	tmp = ft_make_str_without_one_letter_free_str(tmp, 39);
	tmp = ft_make_str_without_one_letter_free_str(tmp, '"');
	return (tmp);
}

void	check_redirection_append(char **s, int i)
{
	char	*tmp;

	if (s[i] && s[i + 1] && ft_strncmp(s[i], ">>", 2) == 0
		&& ft_strlen(s[i]) == 2)
	{
		tmp = process_tmp(s[i + 1]);
		g_data.output_file = ft_strdup(tmp);
		g_data.append_is_one = 1;
		free(tmp);
	}
}

void	check_redirections(char **s, int i)
{
	char	*tmp;

	if (s[i] && s[i + 1] && ft_strncmp(s[i], ">", 1) == 0 && ft_len(s[i]) < 2)
	{
		tmp = process_tmp(s[i + 1]);
		g_data.output_file = ft_strdup(tmp);
		free(tmp);
	}
	else if (s[i] && s[i + 1] && ft_strncmp(s[i], "<", 1) == 0
		&& ft_len(s[i]) < 2)
	{
		tmp = process_tmp(s[i + 1]);
		g_data.input_file = ft_strdup(tmp);
		free(tmp);
	}
	else if (s[i] && s[i + 1] && ft_strncmp(s[i], "<<", 2) == 0
		&& ft_len(s[i]) == 2)
	{
		g_data.here_doc = ft_strdup(".here_doc_tmp.txt");
		tmp = process_tmp(s[i + 1]);
		g_data.word_here_doc = ft_strdup(tmp);
		free(tmp);
	}
	else
		check_redirection_append(s, i);
}

void	ft_take_infile_outfile_with_new_method(char **s)
{
	int			i;

	i = 0;
	while (s[i])
	{
		check_redirections(s, i);
		i++;
	}
}

void	ft_extract_input_output_file(char *s)
{
	char	**test;

	if (!s)
		return ;
	test = split_in_valid_spaces(s);
	ft_take_infile_outfile_with_new_method(test);
	ft_free_double_pointer(test);
	return ;
}
