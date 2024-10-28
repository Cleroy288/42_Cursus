/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:40:06 by chleroy           #+#    #+#             */
/*   Updated: 2023/06/05 11:42:36 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	ft_find_right_env_line(t_pipex *st)
{
	int	i;

	i = 0;
	while (st->env[i])
	{
		if (ft_strncmp("PATH", st->env[i], 4) == 0)
			break ;
		i++;
	}
	st->path_splitted = ft_split(st->env[i], ':');
	if (!st->path_splitted)
		exit(EXIT_FAILURE);
}

char	*ft_get_path(t_pipex *st, int command_nb)
{
	int		i;
	char	*path_command;
	char	*tmp;

	ft_find_right_env_line(st);
	i = 0;
	while (st->path_splitted[i])
	{
		tmp = ft_strjoin(st->path_splitted[i], "/");
		path_command = ft_strjoin(tmp, st->cmd_args[command_nb][0]);
		if (access(path_command, F_OK | X_OK) == 0)
		{
			free(tmp);
			return (path_command);
		}
		free(tmp);
		free(path_command);
		i++;
	}
	return (NULL);
}
