/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:04:33 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/20 12:54:47 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip_n(char *new, int is_n, int *count, int fin)
{
	while (fin == 1)
	{
		if (ft_strncmp(new + (*count), "-n", 2) == 0)
		{
			(*count) += 2;
			if (new[(*count)] != ' ' && new[(*count)] != 'n')
				fin = 0;
			else
			{
				while (new[(*count)] == 'n')
					(*count)++;
				if (new[(*count)] != ' ')
				{
					fin = 0;
					break ;
				}
				while (new[(*count)] == ' ')
					(*count)++;
				is_n = 1;
			}
		}
		else
			fin = 0;
	}
	return (is_n);
}

void	ft_echo(int nb)
{
	char	*new;
	char	*tmp;
	int		is_n;
	int		count;

	ft_count(&count);
	tmp = go_get_right_command(g_data.initial_command, nb);
	new = ft_magic(tmp);
	free(tmp);
	is_n = ft_skip_n(new, 0, &count, 1);
	while (new[count])
	{
		if (new[count] == '$'
			&& new[count + 1] && new[count + 1] == '?')
		{
			printf("%d", g_data.return_value);
			count += 2;
		}
		else
			printf("%c", new[count++]);
	}
	if (is_n == 0)
		printf("\n");
	free(new);
}

void	ft_env(void)
{
	int		i;

	i = 0;
	while (g_data.env && g_data.env[i])
	{
		if (g_data.env[i][ft_strlen(g_data.env[i]) - 1] != '=')
			printf("%s\n", g_data.env[i]);
		i++;
	}
	g_data.return_value = 0;
}

void	ft_unset(t_env	**lst, char *str)
{
	int		len;
	t_env	*temp;
	t_env	*lst_cpy;

	lst_cpy = *lst;
	len = ft_strlen(str);
	if (ft_strncmp(str, "PATH", 4) == 0)
	{
		g_data.path = NULL;
		g_data.path_splitted = NULL;
	}
	while ((lst_cpy)->next)
	{
		if (ft_strncmp(str, (lst_cpy)->next->key, len) == 0)
		{
			temp = (lst_cpy)->next;
			(lst_cpy)->next = (lst_cpy)->next->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			g_data.size_env_tab--;
			return ;
		}
		lst_cpy = lst_cpy->next;
	}
}

t_env	*ft_tab_to_lst(char **tab)
{
	t_env	*lst;
	t_env	*temp;
	int		j;

	if (!tab || !tab[0])
	{
		lst = ft_lstnew_env(NULL, NULL);
		return (lst);
	}
	lst = ft_lstnew_env(tab[0], NULL);
	j = 1;
	while (tab[j])
	{
		temp = ft_lstnew_env(tab[j], NULL);
		ft_lstadd_back_env(&lst, temp);
		j++;
	}
	return (lst);
}
