/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:41:17 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/06 11:11:59 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_tile_coordinates(t_collision_data *data)
{
	data->offsetx = data->st->sprite_width / 4;
	data->offsety = data->st->sprite_height * 1;
	if (data->i % 3 == 0)
		data->tile_x = data->x;
	else if (data->i % 3 == 1)
		data->tile_x = data->x + data->offsetx;
	else
		data->tile_x = data->x + data->st->sprite_width - 1;
	if (data->i < 3)
		data->tile_y = data->y + data->offsety;
	else if (data->i < 6)
		data->tile_y = data->y + data->st->sprite_height / 2;
	else
		data->tile_y = data->y + data->st->sprite_height - 1;
	data->tile_x /= data->st->map->tile_width;
	data->tile_y /= data->st->map->tile_height;
}

void	get_collision_points(t_collision_data *data)
{
	data->i = 0;
	while (data->i < 9)
	{
		set_tile_coordinates(data);
		data->tiles[data->i][0] = data->tile_x;
		data->tiles[data->i][1] = data->tile_y;
		data->i++;
	}
}

int	is_wall(t_mlx *st, int x, int y)
{
	t_collision_data	data;

	data.x = x;
	data.y = y;
	data.st = st;
	data.points_on_non_wall = 0;
	get_collision_points(&data);
	data.i = 0;
	while (data.i < 9)
	{
		data.tile_x = data.tiles[data.i][0];
		data.tile_y = data.tiles[data.i][1];
		if (st->map->data[data.tile_y][data.tile_x] != '1')
			data.points_on_non_wall++;
		data.i++;
	}
	if (data.points_on_non_wall >= 6)
		return (0);
	else
	{
		st->move_ok = 0;
		return (1);
	}
}
