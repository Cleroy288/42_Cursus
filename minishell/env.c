/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:27:59 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/20 12:54:59 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_find_right_env_line(void)
{
	int	i;

	i = 0;
	if (!g_data.env)
		return ;
	while (g_data.env[i])
	{
		if (ft_strncmp("PATH", g_data.env[i], 4) == 0)
			break ;
		i++;
	}
	g_data.path_splitted = ft_split(g_data.env[i], ':');
	if (!g_data.path_splitted)
		return ;
}

char	*ft_find_line(char *str)
{
	int		i;

	i = 0;
	if (g_data.env == NULL || !str)
		return (NULL);
	while (g_data.env[i])
	{
		if (ft_strncmp(str, g_data.env[i], ft_strlen(str)) == 0)
			break ;
		i++;
	}
	if (g_data.env[i])
		return (g_data.env[i]);
	return (NULL);
}

int	ft_len_env_tab(void)
{
	int		i;

	i = 0;
	while (g_data.env[i])
		i++;
	return (i);
}

void	ft_count(int *count)
{
	if (ft_strlen(g_data.initial_command) == 4)
		(*count) = 4;
	else
		(*count) = 5;
}
