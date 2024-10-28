/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command_for_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:03:49 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:10:14 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_in_valid_pipes(char *s)
{
	int		index[2];
	int		k;
	int		nb;
	char	c;
	char	**ret;

	nb = ft_nb_of_command(s);
	index[0] = 0;
	index[1] = 0;
	k = 0;
	ret = malloc(sizeof(char *) * (nb + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	while (s[index[0]])
	{
		c = 0;
		update_j_index(s, &index[1], &c);
		ret[k] = ft_last_pass(s, &index[0], &index[1]);
		k++;
	}
	ret[k] = NULL;
	return (ret);
}

char	**ft_takout_qoutes_in_command_wh_is_not_echo(char **s)
{
	int		nb;
	int		i;

	i = 0;
	nb = g_data.commands_count;
	while (i < nb)
	{
		if (ft_strncmp(s[i], "echo", 4) == 0)
		{
			i++;
			continue ;
		}
		s[i] = ft_make_str_without_one_letter_free_str(s[i], 39);
		s[i] = ft_make_str_without_one_letter_free_str(s[i], '"');
		i++;
	}
	return (s);
}

void	ft_set_ret_in_command_and_options(void)
{
	int		i;
	int		nb;
	char	**tmp;
	char	*s;

	nb = g_data.commands_count;
	i = 0;
	s = ft_strdup(g_data.treated_command);
	g_data.commands_count = ft_nb_of_command(s);
	tmp = split_in_valid_pipes(s);
	g_data.command_in_pipes = ft_takout_qoutes_in_command_wh_is_not_echo(tmp);
	while (i < nb)
	{
		g_data.commands[i] = ft_split(g_data.command_in_pipes[i], 32);
		if (i != nb)
			i++;
	}
	free(s);
	ft_free_double_pointer(tmp);
	tmp = NULL;
}

void	ft_extract_commands_and_options(void)
{
	g_data.commands_count = ft_nb_of_command(g_data.treated_command);
	ft_set_ret_in_command_and_options();
}

void	ft_create_command_with_no_in_out_file_or_redirections(void)
{
	char	*test;	

	test = ft_strdup(g_data.initial_command);
	test = ft_str_without_w_free_str(test, g_data.input_file);
	test = ft_str_without_w_free_str(test, g_data.output_file);
	if (g_data.output_file)
		test = ft_str_without_w_free_str(test, ">>");
	if (g_data.word_here_doc)
		test = ft_str_without_w_free_str(test, "<<");
	if (g_data.input_file)
		test = ft_make_str_without_one_letter_free_str(test, '<');
	if (g_data.output_file)
		test = ft_make_str_without_one_letter_free_str(test, '>');
	test = ft_str_without_w_free_str(test, g_data.word_here_doc);
	if (g_data.here_doc && ft_strncmp(test, "cat", 3) == 0
		&& g_data.commands_count == 0 && ft_strlen(test) == 3
		&& !g_data.here_doc)
		test = ft_join_and_set_char(test, g_data.here_doc, ' ');
	free(g_data.treated_command);
	g_data.treated_command = ft_strdup(test);
	free(test);
}
