/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_line_to_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:45:03 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/02 18:52:10 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

char	**arr_dup(t_map **map)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *)
			* (get_arr_size((void **)(*map)->map_array) + 2));
	if (!new)
		return (NULL);
	i = 0;
	while ((*map)->map_array && (*map)->map_array[i])
	{
		new[i] = ft_strdup((*map)->map_array[i]);
		if (!new[i])
		{
			free_arr((void **)new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	new[i + 1] = NULL;
	return (new);
}

char	**add_line_to_arr(t_map **map, char **file_arr, int i)
{
	char	**new;
	int		j;

	new = arr_dup(map);
	if (!new)
	{
		free_arr((void **)file_arr);
		print_error_exit(map, "Malloc failed\n", EXIT_FAILURE);
	}
	j = 0;
	while (new[j])
		j++;
	new[j] = ft_strdup(file_arr[i]);
	if (!new[j])
	{
		free_arr((void **)file_arr);
		free_arr((void **)new);
		print_error_exit(map, "Malloc failed\n", EXIT_FAILURE);
	}
	new[j + 1] = NULL;
	free_arr((void **)(*map)->map_array);
	return (new);
}
