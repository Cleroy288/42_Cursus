/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fc_color_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:10:02 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/02 18:18:00 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

bool	parse_color_line(char *line)
{
	int	i;

	if (!line)
		return (false);
	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (false);
		i++;
	}
	return (true);
}

void	ca_malloc_fail_free(t_map **map, char **tmp_arr)
{
	free_arr((void **)tmp_arr);
	print_error_exit(map, "Malloc failed\n", EXIT_FAILURE);
}

void	sl_malloc_fail_free(t_map **map, char **tmp_arr, int *color_arr)
{
	free(color_arr);
	free_arr((void **)tmp_arr);
	print_error_exit(map, "Malloc failed\n", EXIT_FAILURE);
}

void	wrong_format_free(t_map **map, char **tmp_arr, int *color_arr)
{
	free(color_arr);
	free_arr((void **)tmp_arr);
	print_error_exit(map, "Wrong color format\n", EXIT_FAILURE);
}
