/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:35:00 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 16:37:46 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_functions_in_exit(int return_value)
{
	ft_free_function();
	ft_free_env();
	if (return_value != 0)
		exit(return_value);
	else
		exit(EXIT_SUCCESS);
}

void	ft_verif_exit(char *ret)
{
	int		i;
	char	**ret_split;
	int		return_value;

	i = -1;
	if (!ret)
		return ;
	ret_split = ft_split(ret, 32);
	while (ret_split[++i])
	{
		if (ft_strncmp(ret_split[i], "exit", 4) == 0)
		{
			if (ft_strncmp(ret_split[i + 1], "|", 1) != 0)
			{
				return_value = ft_atoi(ret_split[i + 1]);
				if (!return_value)
					return_value = 255;
				ft_free_functions_in_exit(return_value);
			}
			else if (ft_modify_shlvl(1))
				ft_free_functions_in_exit(0);
		}
	}
	ft_free_double_pointer(ret_split);
}

char	*ft_remove_quotes(const char *str)
{
	char	*new_str;
	char	c;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	c = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == 39) && i == 0)
			c = str[i];
		else if (str[i] == c)
			i++;
		new_str[j++] = str[i];
		if (str[i])
			i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	ft_create_new_command(char *str, char **new_command, int j)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|')
		{
			if ((*new_command)[j - 1] != ' ')
				(*new_command)[j++] = ' ';
			(*new_command)[j++] = str[i];
			if (str[i + 1] != '\0' && str[i + 1] != ' ')
				(*new_command)[j++] = ' ';
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if (i > 0 && (*new_command)[j - 1] != ' ')
				(*new_command)[j++] = ' ';
			(*new_command)[j++] = str[i];
			if (str[i + 1] == str[i]
				|| (str[i + 1] != '\0' && str[i + 1] != ' '))
				(*new_command)[j++] = str[++i];
		}
		else
			(*new_command)[j++] = str[i];
	}
}

void	ft_set_spaces_in_command(void)
{
	int		j;
	char	*str;
	char	*new_command;

	j = 0;
	if (g_data.initial_command == NULL)
		return ;
	str = ft_strdup(g_data.initial_command);
	if (!str)
		return ;
	new_command = ft_calloc(ft_strlen(str) * 3 + 1, sizeof(char));
	if (!new_command)
	{
		free(str);
		return ;
	}
	ft_create_new_command(str, &new_command, j);
	free(str);
	g_data.initial_command = ft_strdup(new_command);
	free(new_command);
}
