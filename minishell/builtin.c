/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:11:33 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 18:05:59 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_lst_to_tab(t_env *lst, char **tab)
{
	char	**temp;
	int		i;

	i = 0;
	if (!lst->key)
		printf("Error in internal system, contact your administrator\n");
	temp = malloc(sizeof(char *) * (ft_lstsize_env(lst) + 1));
	if (!temp)
		exit(EXIT_FAILURE);
	while (lst)
	{
		if (lst->value != NULL)
			temp[i] = ft_join_and_set_char(lst->key, lst->value, '=');
		else
			temp[i] = ft_strdup(lst->key);
		if (!temp[i])
			return (NULL);
		lst = lst->next;
		i++;
	}
	temp[i] = NULL;
	ft_free_double_pointer(tab);
	return (temp);
}

int	ft_dispach(int i, t_env *lst, char buf[1024], int j)
{
	if ((ft_strncmp(g_data.commands[i][0], "cd", 2) == 0)
		|| (ft_strncmp(g_data.commands[i][0], "OLDPWD", 6) == 0))
		return (1);
	else if (ft_strncmp(g_data.commands[i][0], "echo", 4) == 0)
		ft_echo(i);
	else if (ft_strncmp(g_data.commands[i][0], "export", 7) == 0)
	{
		if (g_data.commands[i][1] == NULL)
			ft_export_basique();
		else
			ft_export_modify(&lst, g_data.commands[i][1], i);
	}
	else if (ft_strncmp(g_data.commands[i][0], "unset", 5) == 0)
	{
		while (g_data.commands[i][++j])
			ft_unset(&lst, g_data.commands[i][j]);
	}
	else if (ft_strncmp(g_data.commands[i][0], "pwd", 3) == 0)
		printf("%s\n", getcwd(buf, 1024));
	else if (ft_strncmp(g_data.commands[i][0], "env", 3) == 0)
		ft_env();
	else
		return (0);
	return (1);
}

void	ft_print_error(void)
{
	printf("Variable not found\n");
	g_data.return_value = 1;
}

int	ft_builtin(int i)
{
	t_env	*lst;
	int		ret;
	char	buf[1024];
	char	*line;

	if (!g_data.commands[i] || !g_data.env)
		return (0);
	lst = ft_tab_to_lst(g_data.env);
	if (g_data.commands[i][0][0] == '$')
	{
		if (ft_find_line(g_data.commands[i][0] + 1))
		{
			line = ft_find_line(g_data.commands[i][0] + 1);
			printf("%s\n", line + ft_strlen(g_data.commands[i][0] + 1) + 1);
		}
		else
			ft_print_error();
		return (1);
	}
	ret = ft_dispach(i, lst, buf, -1);
	g_data.env = ft_lst_to_tab(lst, g_data.env);
	ft_lstclear_env(lst);
	return (ret);
}
