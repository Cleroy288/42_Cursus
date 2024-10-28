/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:30:25 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/03 17:17:03 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

bool	check_valid_way(char **cpy, int i, int j)
{
	if (i == 0 || j == 0)
		return (false);
	if (!cpy[i + 1] || !cpy[i][j + 1])
		return (false);
	if (is_set(cpy[i - 1][j], " \0")
		|| is_set(cpy[i + 1][j], " \0")
		|| is_set(cpy[i][j - 1], " \0")
		|| is_set(cpy[i][j + 1], " \0"))
		return (false);
	return (true);
}

void	parse_map(t_map **map)
{
	char	**cpy;
	int		i;
	int		j;

	cpy = (*map)->map_array;
	i = 0;
	while (cpy[i])
	{
		j = 0;
		while (cpy[i][j])
		{
			if (is_set(cpy[i][j], "0NSWE") && !check_valid_way(cpy, i, j))
				print_error_exit(map, "Map is not fully closed\n", EXIT_FAILURE);
			j++;
		}
		i++;
	}
}
