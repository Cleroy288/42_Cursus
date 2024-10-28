/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fc_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:25:35 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/03 15:23:39 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

int	*get_colors(t_map **map, char **tmp_arr)
{
	int		*color_arr;
	char	**split_line;

	color_arr = malloc(sizeof(int) * 3);
	if (!color_arr)
		ca_malloc_fail_free(map, tmp_arr);
	split_line = ft_split(tmp_arr[1], ',');
	if (!split_line)
		sl_malloc_fail_free(map, tmp_arr, color_arr);
	if (!parse_color_line(tmp_arr[1]) || get_arr_size((void **)split_line) != 3
		|| ft_strlen(split_line[R]) > 3 || ft_strlen(split_line[G]) > 3
		|| ft_strlen(split_line[B]) > 3)
	{
		free_arr((void **)split_line);
		wrong_format_free(map, tmp_arr, color_arr);
	}
	color_arr[R] = ft_atoi(split_line[R]);
	color_arr[G] = ft_atoi(split_line[G]);
	color_arr[B] = ft_atoi(split_line[B]);
	free_arr((void **)split_line);
	if (color_arr[R] < 0 || color_arr[R] > 255
		|| color_arr[G] < 0 || color_arr[G] > 255
		|| color_arr[B] < 0 || color_arr[B] > 255)
		wrong_format_free(map, tmp_arr, color_arr);
	return (color_arr);
}

void	get_f_color(t_map **map, char **file_arr, char **tmp_arr)
{
	if ((*map)->textures->f_color)
	{
		free_arr((void **)tmp_arr);
		free_arr((void **)file_arr);
		print_error_exit(map, "Duplicate symbol \"F\"\n", EXIT_FAILURE);
	}
	(*map)->textures->f_color = get_colors(map, tmp_arr);
	if (!(*map)->textures->f_color)
	{
		free_arr((void **)tmp_arr);
		free_arr((void **)file_arr);
		print_error_exit(map, "Malloc failed\n", EXIT_FAILURE);
	}
}

void	get_c_color(t_map **map, char **file_arr, char **tmp_arr)
{
	if ((*map)->textures->c_color)
	{
		free_arr((void **)tmp_arr);
		free_arr((void **)file_arr);
		print_error_exit(map, "Duplicate symbol \"C\"\n", EXIT_FAILURE);
	}
	(*map)->textures->c_color = get_colors(map, tmp_arr);
	if (!(*map)->textures->c_color)
	{
		free_arr((void **)tmp_arr);
		free_arr((void **)file_arr);
		print_error_exit(map, "Malloc failed\n", EXIT_FAILURE);
	}
}

void	get_fc_color(t_map **map, char **file_arr, char **tmp_arr, int type)
{
	if (type == e_f)
		get_f_color(map, file_arr, tmp_arr);
	else if (type == e_c)
		get_c_color(map, file_arr, tmp_arr);
}
