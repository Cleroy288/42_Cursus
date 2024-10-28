/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:55:48 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 18:25:04 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_count(char *s)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (s[i])
	{
		if (s[i] == '|')
			pipe_count++;
		i++;
	}
	if (pipe_count > 100)
	{
		printf("There is too much step bro\n");
		return (1);
	}
	return (0);
}

int	check_escape_validity(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\\' && ft_search_for_character(s, '\\') == 0)
		{
			printf("bad command\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_consecutive_pipes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '|')
		{
			i++;
			while (s[i] == 32)
				i++;
			if (s[i] == '|')
				return (1);
		}
		if (s[i])
			i++;
	}
	return (0);
}

int	ft_process_the_input_validity_quotes(char *s)
{
	if (!s)
		return (1);
	if (check_pipe_count(s)
		|| check_escape_validity(s)
		|| check_consecutive_pipes(s))
		return (1);
	return (0);
}
