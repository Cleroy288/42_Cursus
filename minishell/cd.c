/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:26:15 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:33:34 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_command_cd_part_2(char **path)
{
	char	cwd[PATH_MAX];

	if (!*path)
		return (1);
	if (*path && ft_strlen(*path) > 1 && ft_strncmp(*path, "HOME=", 5) == 0)
		(*path) = ft_str_without_w((*path), "HOME=");
	else
		(*path) = ft_str_without_w((*path), "OLDPWD=");
	if (chdir((*path)) == -1)
	{
		perror("chdir");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_update_pwd(cwd);
	free(*path);
	*path = NULL;
	return (0);
}

void	ft_is_command_cd(void)
{
	int		i[2];
	char	buf[1024];
	char	*path;
	char	*oldpwd;

	i[0] = 0;
	if (!g_data.commands[0])
		return ;
	while (g_data.commands[i[0]] && i[0] < g_data.commands_count)
	{
		if (g_data.commands[i[0]][0]
			&& ft_strncmp(g_data.commands[i[0]][0], "cd", 2) == 0)
		{
			if (ft_cd_option(i[0], &path) == 1)
				return ;
			oldpwd = ft_find_line("PWD");
			if (!oldpwd || oldpwd == NULL)
				oldpwd = getcwd(buf, sizeof(buf));
			ft_update_old_pwd(oldpwd + 4);
			if (ft_is_command_cd_part_2(&path) == 1)
				return ;
		}
		i[0]++;
	}
}

int	ft_join_path(int nb, char **path_command, int i)
{
	char	*tmp;

	tmp = ft_strjoin(g_data.path_splitted[i], "/");
	if (!tmp)
		return (1);
	if (!g_data.commands[nb])
		return (1);
	if (g_data.commands[nb][0] && tmp)
	{
		(*path_command) = ft_strjoin(tmp, g_data.commands[nb][0]);
		if (access((*path_command), F_OK | X_OK) == 0)
		{
			free(tmp);
			return (2);
		}
		free(tmp);
		free((*path_command));
	}
	return (0);
}

void	ft_execute(int nb)
{
	char	*tmp;

	tmp = ft_str_without_w(g_data.commands[nb][0], "/bin/");
	if (ft_strncmp(g_data.commands[nb][0], "./", 2) == 0
		|| ft_strncmp(g_data.commands[nb][0], "/", 1) == 0)
	{
		if (ft_strncmp(g_data.commands[nb][0], "/", 1) == 0)
		{
			g_data.path = ft_strdup(g_data.commands[nb][0]);
			g_data.commands[nb][0] = tmp;
		}
		ft_signal_handler_child();
		signal(SIGQUIT, SIG_DFL);
		g_data.status = 2;
		execve(g_data.path, &g_data.commands[nb][0], g_data.env);
	}
	else if (g_data.commands[nb][0] != NULL
				&& ft_strlen(g_data.commands[nb][0]) > 1)
		printf("minishell: [%s]: command not found\n", g_data.commands[nb][0]);
}

char	*ft_get_path(int nb, int i)
{
	int		ret;
	char	*path_command;
	char	buf[1024];

	if (ft_strncmp(g_data.initial_command, "./minishell", 11) == 0)
		ft_modify_shlvl(0);
	if (g_data.initial_command[0] == '.')
		return (getcwd(buf, 1024));
	ft_find_right_env_line();
	if (g_data.path_splitted == NULL)
	{
		g_data.return_value = 127;
		return (NULL);
	}
	while (g_data.path_splitted[i])
	{
		ret = ft_join_path(nb, &path_command, i);
		if (ret == 1)
			return (NULL);
		else if (ret == 2)
			return (path_command);
		i++;
	}
	ft_execute(nb);
	exit (1);
}
