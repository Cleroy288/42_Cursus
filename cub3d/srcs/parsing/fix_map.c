/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:15:24 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/02 17:18:38 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

int	get_line_length(t_map **map)
{
	int	i;
	int	len;
	int	tmp_len;

	len = 0;
	i = 0;
	while ((*map)->map_array && (*map)->map_array[i])
	{
		tmp_len = ft_strlen((*map)->map_array[i]);
		if (tmp_len > len)
			len = tmp_len;
		i++;
	}
	return (len);
}

void	init_matrix(t_map **map, char **new, int arr_len, int line_len)
{
	int	i;

	i = 0;
	while (i < arr_len)
	{
		new[i] = calloc_with_spaces(sizeof(char), line_len + 1);
		if (!new[i])
		{
			free_arr((void **)new);
			print_error_exit(map, "Malloc faield\n", EXIT_FAILURE);
		}
		i++;
	}
	new[i] = NULL;
}

void	fix_map(t_map **map)
{
	char	**new;
	int		arr_len;
	int		line_len;
	int		i;

	arr_len = get_arr_size((void **)(*map)->map_array);
	new = malloc(sizeof(char *) * (arr_len + 1));
	if (!new)
		print_error_exit(map, "Malloc failed\n", EXIT_FAILURE);
	line_len = get_line_length(map);
	init_matrix(map, new, arr_len, line_len);
	i = 0;
	while ((*map)->map_array && (*map)->map_array[i])
	{
		not_null_terminated_strlcpy(new[i], (*map)->map_array[i],
			ft_strlen((*map)->map_array[i]));
		i++;
	}
	new[i] = NULL;
	free_arr((void **)(*map)->map_array);
	(*map)->map_array = new;
}
