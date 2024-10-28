/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:39:05 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/03 17:20:13 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	print_arr(char **arr)
{
	ft_printf(1, "\n ---PRINTING FILE---\n\n");
	while (*arr)
	{
		ft_printf(1, "[%s]\n", *arr);
		arr++;
	}
	ft_printf(1, "\n -------------------\n\n");
}

void	print_map(t_map **map) //tmp
{
	int	i;

	i = 0;
	ft_printf(1, "\n ---PRINTING MAP---\n\n");
	while ((*map)->map_array && (*map)->map_array[i])
	{
		ft_printf(1, "[%s]\n", (*map)->map_array[i]);
		i++;
	}
	ft_printf(1, "\n ------------------\n\n");
}

void	parsing(t_map **map, char *map_path)
{
	char	**file_arr;
	int		map_fd;

	map_fd = check_file(map, map_path);
	file_arr = get_file_arr(map, map_fd);
	// print_arr(file_arr); //tmp
	get_map_datas(map, file_arr);
	get_map_arr(map, file_arr);
	free_arr((void **)file_arr);
	fix_map(map);
	// print_map(map); //tmp
	parse_map(map);
}
