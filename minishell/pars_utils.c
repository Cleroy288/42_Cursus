/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:37:13 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 16:37:27 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_modify_shlvl(int modif)
{
	char	*tmp;
	int		i;
	int		j;

	j = ft_atoi(ft_find_line("SHLVL") + 6);
	i = 0;
	if (!g_data.env)
		return (0);
	while (g_data.env[i])
	{
		if (g_data.env[i] && ft_strncmp("SHLVL", g_data.env[i], 5) == 0)
		{
			free(g_data.env[i]);
			tmp = ft_strdup("SHLVL=");
			if (modif == 1)
				g_data.env[i] = ft_strjoin_free_both(tmp, ft_itoa(j - 1));
			else
				g_data.env[i] = ft_strjoin_free_both(tmp, ft_itoa(j + 1));
			break ;
		}
		i++;
	}
	return (1);
}

void	ft_free_env(void)
{
	int	i;

	i = 0;
	if (!g_data.env)
		return ;
	while (g_data.env[i])
	{
		free(g_data.env[i]);
		g_data.env[i] = NULL;
		i++;
	}
}
