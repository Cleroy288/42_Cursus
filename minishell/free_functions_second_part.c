/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_second_part.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:23:32 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:24:48 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_path_splitted(void)
{
	int	i;

	i = 0;
	while (g_data.path_splitted != NULL)
	{
		if (g_data.path_splitted[0])
		{
			while (g_data.path_splitted[i])
			{
				free(g_data.path_splitted[i]);
				g_data.path_splitted[i] = NULL;
				i++;
			}
		}
	}
}

void	ft_free_path(void)
{
	if (g_data.path != NULL)
	{
		free(g_data.path);
		g_data.path = NULL;
	}
}

void	ft_free_one_tab_in_commands(int index)
{
	int	i;

	i = 0;
	if (g_data.commands[index][i] != NULL)
	{
		while (g_data.commands[index][i] != NULL)
		{
			free(g_data.commands[index][i]);
			g_data.commands[index][i] = NULL;
			i++;
		}
	}
}

void	ft_free_commands(void)
{
	int	i;

	i = 0;
	while (g_data.commands[i] != NULL)
	{
		if (g_data.commands[i])
			ft_free_one_tab_in_commands(i);
		if (g_data.commands[i])
			i++;
	}
}

void	ft_free_treated_command(void)
{
	if (g_data.treated_command != NULL)
	{
		free(g_data.treated_command);
		g_data.treated_command = NULL;
	}
}
