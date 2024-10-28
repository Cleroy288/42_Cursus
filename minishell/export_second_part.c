/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_second_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:48:08 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:48:49 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_info(int len, t_env *temp, char *str, char *tmp)
{
	char	*add;

	if (str[len] == '+')
	{
		add = ft_strjoin(temp->value, tmp);
		free(temp->value);
		temp->value = add;
		return ;
	}
	free(temp->value);
	temp->value = ft_strdup(tmp);
}

char	*ft_remove(char *tmp, int nb_of_command)
{
	char	*tmp2;

	tmp = go_get_right_command(g_data.treated_command, nb_of_command);
	tmp2 = strdup(tmp);
	if (tmp)
		free(tmp);
	tmp = extract_everything_after_char(tmp2, '=');
	tmp2 = strdup(tmp);
	if (tmp)
		free(tmp);
	tmp = ft_make_str_without_one_letter_free_str(tmp2, '"');
	tmp2 = strdup(tmp);
	if (tmp)
		free(tmp);
	tmp = ft_make_str_without_one_letter_free_str(tmp2, '\'');
	return (tmp);
}

void	ft_export_modify(t_env **lst, char *str, int nb_of_command)
{
	t_env	*temp;
	int		len;
	char	*tmp;

	tmp = NULL;
	tmp = ft_remove(tmp, nb_of_command);
	len = 0;
	temp = *lst;
	while (str[len] && str[len] != '=')
		len++;
	if (str[len - 1] == '+')
		len--;
	while (temp->next)
	{
		if (ft_strncmp(temp->key, str, len) == 0)
			return (ft_add_info(len, temp, str, tmp));
		temp = temp->next;
	}
	if (ft_strncmp(temp->key, str, len) == 0)
		ft_add_info(len, temp, str, tmp);
	ft_export_add(&temp, tmp, str);
	g_data.size_env_tab++;
	free(tmp);
}

void	ft_increment(int *end, int *ret, char **str, int incr)
{
	(*end)++;
	(*ret)++;
	(*str) += incr;
}

int	ft_is_n(char **str)
{
	int	end;
	int	ret;

	end = 1;
	ret = 0;
	while ((*str) && end == 1)
	{
		end = 0;
		while ((*str)[0] == ' ')
			(*str)++;
		if (ft_strncmp(*str, "-n ", 3) == 0)
		{
			ft_increment(&end, &ret, str, 3);
		}
		else if ((*str)[0] == '-')
		{
			ft_increment(&end, &ret, str, 1);
			while ((*str)[0] == 'n')
				(*str)++;
		}
	}
	while ((*str)[0] == ' ')
		(*str)++;
	return (ret);
}
