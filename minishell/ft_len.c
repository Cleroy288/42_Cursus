/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:31:42 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:33:19 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_cd_option(int i, char **path)
{
	(*path) = g_data.commands[i][1];
	if ((*path) == NULL)
	{
		(*path) = ft_find_line("HOME");
		if ((*path) == NULL)
		{
			perror("getenv: HOME not set");
			return (1);
		}
	}
	if (ft_strncmp((*path), "-", 2) == 0)
	{
		(*path) = ft_find_line("OLDPWD");
		if ((*path) == NULL)
		{
			perror("getenv: OLDPWD not set");
			return (1);
		}
	}
	return (0);
}
