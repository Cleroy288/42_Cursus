/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:25:35 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 10:20:11 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_old_pwd(char *new_path)
{
	int		i;
	char	*new_pwd;

	new_pwd = ft_strjoin("OLDPWD=", new_path);
	if (!new_pwd)
		return ;
	i = 0;
	while (i < g_data.size_env_tab)
	{
		if (ft_strncmp(g_data.env[i], "OLDPWD=", 7) == 0
			&& ft_strncmp(g_data.initial_command, "cd -", 4) != 0)
		{
			free(g_data.env[i]);
			g_data.env[i] = new_pwd;
			return ;
		}
		else
		{
			g_data.env[i] = new_pwd;
			return ;
		}
		i++;
	}
	free(new_pwd);
}

void	ft_update_pwd(char *new_path)
{
	int		i;
	char	*new_pwd;
	char	*temp;

	new_pwd = ft_strjoin("PWD=", new_path);
	if (!new_pwd)
		return ;
	i = 0;
	while (i < g_data.size_env_tab)
	{
		if (ft_strncmp(g_data.env[i], "PWD=", 4) == 0)
		{
			temp = ft_strdup(g_data.env[i]);
			free(g_data.env[i]);
			g_data.env[i] = ft_strdup(new_pwd);
			if (g_data.env[i] == NULL)
				g_data.env[i] = temp;
			free(new_pwd);
			free(temp);
			return ;
		}
		i++;
	}
	free(new_pwd);
}
