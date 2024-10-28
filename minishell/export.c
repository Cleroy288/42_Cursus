/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:46:02 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:47:03 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_iswhitespace(char c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

void	ft_display(int *tab, int i[4])
{
	i[0] = g_data.size_env_tab;
	while (0 < i[0])
	{
		i[1] = 0;
		while (i[1] < g_data.size_env_tab)
		{
			if (tab[i[1]] == i[0])
			{
				i[2] = 0;
				ft_putstr_fd("declare -x ", 1);
				while (g_data.env[i[1]][i[2]])
				{
					if (g_data.env[i[1]][i[2]] == '=' &&
						ft_iswhitespace(g_data.env[i[1]][i[2] + 1]) == 0)
						break ;
					ft_putchar_fd(g_data.env[i[1]][i[2]], 1);
					i[2]++;
				}
				ft_putstr_fd("\n", 1);
				break ;
			}
			i[1]++;
		}
		i[0]--;
	}
}

void	ft_export_basique(void)
{
	int		*tab;
	int		i;
	int		j;
	int		count[4];
	int		len;

	i = 0;
	tab = malloc(sizeof(int) * g_data.size_env_tab);
	if (!tab)
		exit(EXIT_FAILURE);
	while (i < g_data.size_env_tab)
	{
		j = 0;
		count[3] = 0;
		while (j < g_data.size_env_tab)
		{
			len = ft_strlen(g_data.env[j]);
			if (ft_strncmp(g_data.env[i], g_data.env[j], len) < 0)
				count[3]++;
			j++;
		}
		tab[i] = count[3];
		i++;
	}
	ft_display(tab, count);
}

void	ft_export_add(t_env **lst, char *str, char *content)
{
	t_env	*temp;

	temp = ft_lstnew_env(content, str);
	ft_lstadd_back_env(lst, temp);
}

char	*extract_everything_after_char(char *s, char c)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			break ;
		}
		i++;
	}
	while (s[i + j])
		j++;
	ret = ft_substr(s, i, j);
	if (!ret)
		return (NULL);
	free(s);
	return (ret);
}
