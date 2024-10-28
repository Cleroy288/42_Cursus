/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:20:20 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/03 14:59:28 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	get_no_wall_texture(t_map **map, char **file_arr, char **tmp_arr)
{
	if ((*map)->textures->no_texture_path)
	{
		ft_printf(2, "Error\nDuplicate symbol \"NO\"\n");
		free_arr((void **)tmp_arr);
		free_arr((void **)file_arr);
		free_map(map);
		exit(EXIT_FAILURE);
	}
	(*map)->textures->no_texture_path = ft_strdup(tmp_arr[1]);
	if (!(*map)->textures->no_texture_path)
	{
		free_arr((void **)tmp_arr);
		free_arr((void **)file_arr);
		print_error_exit(map, "Malloc error\n", EXIT_FAILURE);
	}
}

void	get_so_wall_texture(t_map **map, char **file_arr, char **tmp_arr)
{
	if ((*map)->textures->so_texture_path)
	{
		ft_printf(2, "Error\nDuplicate symbol \"SO\"\n");
		free_arr((void **)tmp_arr);
		free_arr((void **)file_arr);
		free_map(map);
		exit(EXIT_FAILURE);
	}
	(*map)->textures->so_texture_path = ft_strdup(tmp_arr[1]);
	if (!(*map)->textures->so_texture_path)
	{
		free_arr((void **)tmp_arr);
		free_arr((void **)file_arr);
		print_error_exit(map, "Malloc error\n", EXIT_FAILURE);
	}
}

void	get_we_wall_texture(t_map **map, char **file_arr, char **tmp_arr)
{
	if ((*map)->textures->we_texture_path)
	{
		ft_printf(2, "Error\nDuplicate symbol \"WE\"\n");
		free_arr((void **)tmp_arr);
		free_arr((void **)file_arr);
		free_map(map);
		exit(EXIT_FAILURE);
	}
	(*map)->textures->we_texture_path = ft_strdup(tmp_arr[1]);
	if (!(*map)->textures->we_texture_path)
	{
		free_arr((void **)tmp_arr);
		free_arr((void **)file_arr);
		print_error_exit(map, "Malloc error\n", EXIT_FAILURE);
	}
}

void	get_ea_wall_texture(t_map **map, char **file_arr, char **tmp_arr)
{
	if ((*map)->textures->ea_texture_path)
	{
		ft_printf(2, "Error\nDuplicate symbol \"EA\"\n");
		free_arr((void **)tmp_arr);
		free_arr((void **)file_arr);
		free_map(map);
		exit(EXIT_FAILURE);
	}
	(*map)->textures->ea_texture_path = ft_strdup(tmp_arr[1]);
	if (!(*map)->textures->ea_texture_path)
	{
		free_arr((void **)tmp_arr);
		free_arr((void **)file_arr);
		print_error_exit(map, "Malloc error\n", EXIT_FAILURE);
	}
}

void	get_wall_texture(t_map **map, char **file_arr, char **tmp_arr, int type)
{
	if (type == e_no)
		get_no_wall_texture(map, file_arr, tmp_arr);
	else if (type == e_so)
		get_so_wall_texture(map, file_arr, tmp_arr);
	else if (type == e_we)
		get_we_wall_texture(map, file_arr, tmp_arr);
	else if (type == e_ea)
		get_ea_wall_texture(map, file_arr, tmp_arr);
}
