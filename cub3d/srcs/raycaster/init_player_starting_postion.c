/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_starting_postion.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:51:47 by chleroy           #+#    #+#             */
/*   Updated: 2023/10/14 13:01:51 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	set_player_angle(t_gen *gen, char tile)
{
	if (tile == 'N')
		gen->pa = 1.5 * PI;
	else if (tile == 'S')
		gen->pa = 0.5 * PI;
	else if (tile == 'E')
		gen->pa = 0;
	else if (tile == 'W')
		gen->pa = PI;
}

int	ft_len_2d_tab(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	init_player_starting_position(t_gen *gen)
{
	int		x;
	int		y;
	char	tile;

	gen->map_y = ft_len_2d_tab(gen->map->map_array);
	gen->map_x = ft_strlen(gen->map->map_array[0]);
	y = 0;
	while (y < gen->map_y)
	{
		x = 0;
		while (x < gen->map_x)
		{
			tile = gen->map->map_array[y][x];
			if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
			{
				gen->px = x * gen->map_s + gen->map_s / 2;
				gen->py = y * gen->map_s + gen->map_s / 2;
				set_player_angle(gen, tile);
				return ;
			}
			x++;
		}
		y++;
	}
}
