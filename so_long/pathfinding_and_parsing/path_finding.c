/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 10:43:09 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/04 10:46:22 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	**copy_map(char **map_real, int map_height, int map_width)
{
	char	**map_copy;
	int		i;
	int		j;

	i = 0;
	map_copy = malloc(sizeof(char *) * map_height);
	while (i < map_height)
	{
		map_copy[i] = malloc(sizeof(char) * (map_width + 1));
		j = 0;
		while (map_real[i][j] != '\0')
		{
			map_copy[i][j] = map_real[i][j];
			j++;
		}
		map_copy[i][j] = '\0';
		i++;
	}
	return (map_copy);
}

int	ft_pathfinding(char **map_real, int itm, int x, int y)
{
	static int	item;
	char		**map;

	item = itm;
	map = map_real;
	if (item == 0)
		return (0);
	if (map[y][x] == 'C' || map[y][x] == 'E')
		item += -1;
	map[y][x] = '2';
	if (map[y - 1][x] != '1' && map[y - 1][x] != '2')
		ft_pathfinding(map, item, x, y - 1);
	if (map[y + 1][x] != '1' && map[y + 1][x] != '2')
		ft_pathfinding(map, item, x, y + 1);
	if (map[y][x - 1] != '1' && map[y][x - 1] != '2')
		ft_pathfinding(map, item, x - 1, y);
	if (map[y][x + 1] != '1' && map[y][x + 1] != '2')
		ft_pathfinding(map, item, x + 1, y);
	if (item == 0)
		return (1);
	return (-1);
}
