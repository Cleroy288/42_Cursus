/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:00:00 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/06 11:16:49 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_collectible(t_mlx *st, int tile_x, int tile_y)
{
	if (st->map->data[tile_y][tile_x] == 'C')
	{
		st->map->data[tile_y][tile_x] = '0';
		st->collectibles_count--;
		draw_collectibles_count(st);
	}
}

void	handle_exit(t_mlx *st)
{
	if (is_player_on_exit(st) == 1)
	{
		ft_putstr_fd("You've reahced exit !\n", 1);
		exit(0);
	}
}

void	handle_movement(int keycode, int step, t_mlx *st)
{
	int	tile_x;
	int	tile_y;

	st->moving = 1;
	tile_x = st->x_pos / st->map->tile_width ;
	tile_y = st->y_pos / st->map->tile_height;
	if (keycode == 126)
		handle_up(step, st);
	if (keycode == 125)
		handle_down(step, st);
	if (keycode == 123)
		handle_left(step, st);
	if (keycode == 124 && st->map->data[tile_y][tile_x + 1] != '1')
		handle_right(step, st);
	ft_paint(st);
	handle_collectible(st, tile_x, tile_y);
	handle_exit(st);
	st->moving = 0;
}

int	key_pressed(int keycode, t_mlx *st)
{
	int	step;

	if (st->move_ok == 1)
	{
		st->write_term += 1;
		st->key_press_count++;
		if (st->write_term == 1)
		{
			write (1, "key press count ", ft_strlen("key press count "));
			write(1, ft_itoa(st->key_press_count / 2),
				ft_strlen(ft_itoa(st->key_press_count / 2)));
			write (1, "\n", 1);
		}
		st->write_term = st->write_term % 2;
	}
	step = 24;
	if (keycode == 53)
		exit(0);
	handle_movement(keycode, step, st);
	return (0);
}

void	ft_movement_and_management(t_mlx *st)
{
	mlx_key_hook(st->mlx_win, key_pressed, st);
	mlx_loop_hook(st->mlx, (int (*)(void *))ft_paint, st);
	mlx_loop(st->mlx);
}
