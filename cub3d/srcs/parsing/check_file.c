/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:59:03 by noloupe           #+#    #+#             */
/*   Updated: 2023/09/29 14:04:06 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

int	check_file(t_map **map, char *map_path)
{
	int	map_fd;
	int	len;

	len = ft_strlen(map_path);
	if (ft_strncmp(&map_path[len - 4], ".cub", 4))
		print_error_exit(map, "Wrong map format\n", EXIT_FAILURE);
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		print_error_exit(map, "Could not open file\n", EXIT_FAILURE);
	return (map_fd);
}
