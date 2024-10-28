/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_datas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:27:12 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/02 18:40:28 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

bool	check_datas(t_map **map)
{
	if ((*map)->textures->no_texture_path
		&& (*map)->textures->so_texture_path
		&& (*map)->textures->we_texture_path
		&& (*map)->textures->ea_texture_path
		&& (*map)->textures->f_color
		&& (*map)->textures->c_color)
		return (true);
	return (false);
}

void	get_map_datas(t_map **map, char **file_arr)
{
	int	i;

	i = 0;
	while (file_arr[i])
	{
		treat_line(map, file_arr, i);
		if (check_datas(map))
			break ;
		i++;
	}
}
