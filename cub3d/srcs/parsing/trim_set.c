/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:55:06 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/03 17:21:16 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

int	get_trim_size(char *line, char *set)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (line[i])
	{
		if (!is_set(line[i], set))
			size++;
		i++;
	}
	return (size);
}

char	*trim_set(char *line, char *set)
{
	char	*new;
	int		trim_size;
	int		i;
	int		j;

	if (!line || !set)
		return (NULL);
	trim_size = get_trim_size(line, set);
	new = ft_calloc(sizeof(char), trim_size + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (!is_set(line[i], set))
		{
			new[j] = line[i];
			j++;
		}
		i++;
	}
	return (new);
}
