/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:07:46 by noloupe           #+#    #+#             */
/*   Updated: 2023/09/29 16:14:08 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

t_textures	*textures_init(void)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	if (!textures)
		return (NULL);
	textures->no_texture_path = NULL;
	textures->so_texture_path = NULL;
	textures->we_texture_path = NULL;
	textures->ea_texture_path = NULL;
	textures->f_color = NULL;
	textures->c_color = NULL;
	return (textures);
}

t_map	*map_init(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		print_error_exit(NULL, "Map struct malloc failed\n", EXIT_FAILURE);
	map->map_array = NULL;
	map->textures = textures_init();
	if (!map->textures)
		print_error_exit(&map, "Texture struct malloc failed\n", EXIT_FAILURE);
	return (map);
}
