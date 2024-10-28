/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handels_and_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:47:48 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/06 11:15:48 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_up(int step, t_mlx *st)
{
	int	new_y;

	step = 32;
	new_y = st->y_pos - step;
	if (!is_wall(st, st->x_pos, new_y))
	{
		st->move_ok = 1;
		st->y_pos = new_y;
	}
	st->animation_state = (st->animation_state + 1) % 2;
	if (st->animation_state == 0)
		st->img = st->img_up1;
	else
		st->img = st->img_up2;
}

void	handle_down(int step, t_mlx *st)
{
	int	new_y;

	step = 16;
	new_y = st->y_pos + step;
	if (!is_wall(st, st->x_pos, new_y))
	{
		st->move_ok = 1;
		st->y_pos = new_y;
	}
	st->animation_state = (st->animation_state + 1) % 2;
	if (st->animation_state == 0)
		st->img = st->img_down1;
	else
		st->img = st->img_down2;
}

void	handle_left(int step, t_mlx *st)
{
	int	new_x;

	new_x = st->x_pos - step;
	if (!is_wall(st, new_x, st->y_pos))
	{
		st->move_ok = 1;
		st->x_pos = new_x;
		st->animation_state = (st->animation_state + 1) % 2;
		if (st->animation_state == 0)
			st->img = st->img_left1;
		else
			st->img = st->img_left2;
	}	
}		

void	handle_right(int step, t_mlx *st)
{
	int	new_x;

	new_x = st->x_pos + step;
	if (!is_wall(st, new_x, st->y_pos))
		st->x_pos = new_x;
	st->animation_state = (st->animation_state + 1) % 2;
	if (st->animation_state == 0)
		st->img = st->img_right1;
	else
		st->img = st->img_right2;
}

int	is_player_on_exit(t_mlx *st)
{
	int	tile_x;
	int	tile_y;

	tile_x = st->x_pos / st->map->tile_width;
	tile_y = st->y_pos / st->map->tile_height;
	if (((st->map->data[tile_y][tile_x] == 'E' && st->collectibles_count == 0)))
		return (1);
	else if (st->map->data[tile_y][tile_x] == 'M')
	{
		ft_putstr_fd("you have been eaten by a montser !\n", 2);
		exit(0);
	}
	return (0);
}
