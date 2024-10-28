/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:06:10 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/02 18:51:33 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

bool	is_valid_line(char *line)
{
	char	c;
	int		i;
	int		valid;

	valid = 0;
	i = 0;
	while (line[i])
	{
		c = line[i];
		if (c == '0' || c == '1')
			valid = true;
		if (c != '0' && c != '1' && c != 'N' && c != 'S'
			&& c != 'W' && c != 'E' && c != ' ' && c != '\0')
			return (false);
		i++;
	}
	return (valid);
}

void	get_map_arr(t_map **map, char **file_arr)
{
	int		i;

	if (get_arr_size((void **)file_arr) < 7)
	{
		free_arr((void **)file_arr);
		print_error_exit(map, "Missing map in file\n", EXIT_FAILURE);
	}
	i = 6;
	while (file_arr[i])
	{
		if (!is_valid_line(file_arr[i]))
		{
			free_arr((void **)file_arr);
			print_error_exit(map, "Wrong line in map\n", EXIT_FAILURE);
		}
		(*map)->map_array = add_line_to_arr(map, file_arr, i);
		i++;
	}
}
