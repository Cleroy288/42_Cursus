/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:27:04 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/03 14:54:20 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	get_token_data(t_map **map, char **file_arr, char **tmp_arr, int type)
{
	if (type == e_no || type == e_so || type == e_we || type == e_ea)
		get_wall_texture(map, file_arr, tmp_arr, type);
	else if (type == e_f || type == e_c)
		get_fc_color(map, file_arr, tmp_arr, type);
}

void	check_token(t_map **map, char **file_arr, char **tmp_arr)
{
	if (!tmp_arr[0])
		return ;
	if (!ft_strncmp(tmp_arr[0], "NO", 3))
		get_token_data(map, file_arr, tmp_arr, e_no);
	else if (!ft_strncmp(tmp_arr[0], "SO", 3))
		get_token_data(map, file_arr, tmp_arr, e_so);
	else if (!ft_strncmp(tmp_arr[0], "WE", 3))
		get_token_data(map, file_arr, tmp_arr, e_we);
	else if (!ft_strncmp(tmp_arr[0], "EA", 3))
		get_token_data(map, file_arr, tmp_arr, e_ea);
	else if (!ft_strncmp(tmp_arr[0], "F", 2))
		get_token_data(map, file_arr, tmp_arr, e_f);
	else if (!ft_strncmp(tmp_arr[0], "C", 2))
		get_token_data(map, file_arr, tmp_arr, e_c);
	else
	{
		ft_printf(2, "Error\nUnexpected token \"%s\"\n", tmp_arr[0]);
		free_arr((void **)tmp_arr);
		free_arr((void **)file_arr);
		free_map(map);
		exit(EXIT_FAILURE);
	}
}

void	treat_line(t_map **map, char **file_arr, int i)
{
	char	**tmp_arr;

	tmp_arr = ft_split(file_arr[i], ' ');
	if (!tmp_arr)
	{
		free_arr((void **)file_arr);
		print_error_exit(map, "Malloc failed\n", EXIT_FAILURE);
	}
	if (get_arr_size((void **)tmp_arr) > 2)
	{
		free_arr((void **)file_arr);
		print_error_exit(map, "Wrong line in file\n", EXIT_FAILURE);
	}
	check_token(map, file_arr, tmp_arr);
	free_arr((void **)tmp_arr);
}
