/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:18:20 by noloupe           #+#    #+#             */
/*   Updated: 2023/09/29 16:13:47 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	free_map(t_map **map)
{
	free_arr((void **)(*map)->map_array);
	if ((*map)->textures)
	{
		if ((*map)->textures->no_texture_path)
			free((*map)->textures->no_texture_path);
		if ((*map)->textures->so_texture_path)
			free((*map)->textures->so_texture_path);
		if ((*map)->textures->we_texture_path)
			free((*map)->textures->we_texture_path);
		if ((*map)->textures->ea_texture_path)
			free((*map)->textures->ea_texture_path);
		if ((*map)->textures->f_color)
			free((*map)->textures->f_color);
		if ((*map)->textures->c_color)
			free((*map)->textures->c_color);
	}
	free((*map)->textures);
	free((*map));
}
