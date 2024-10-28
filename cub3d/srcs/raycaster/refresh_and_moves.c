/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_and_moves.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:51:27 by chleroy           #+#    #+#             */
/*   Updated: 2023/10/14 15:06:47 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	move_left(t_gen *gen)
{
	float	new_x;
	float	new_y;

	new_x = gen->px - gen->pdy * (SPEED / 5.0);
	new_y = gen->py + gen->pdx * (SPEED / 5.0);
	if (can_move(new_x, new_y, MOVE_LEFT, gen))
	{
		gen->px = new_x;
		gen->py = new_y;
	}
}

void	move_right(t_gen *gen)
{
	float	new_x;
	float	new_y;

	new_x = gen->px + gen->pdy * (SPEED / 5.0);
	new_y = gen->py - gen->pdx * (SPEED / 5.0);
	if (can_move(new_x, new_y, MOVE_RIGHT, gen))
	{
		gen->px = new_x;
		gen->py = new_y;
	}
}

void	ft_moves(t_gen *gen)
{
	if (gen->move_forward)
		move_forward(gen);
	if (gen->move_backward)
		move_backward(gen);
	if (gen->turn_left)
		turn_left(gen);
	if (gen->turn_right)
		turn_right(gen);
	if (gen->move_left)
		move_left(gen);
	if (gen->move_right)
		move_right(gen);
}

int	refresh(t_gen *gen)
{
	void	*img_ptr;
	char	*data;

	img_ptr = mlx_new_image(gen->mlx_ptr, W_WIDTH, W_HEIGHT);
	data = mlx_get_data_addr(img_ptr, &(int){0}, &(int){0}, &(int){0});
	ft_moves(gen);
	other_drawrays3d(data, W_WIDTH, gen);
	if (gen->map_x < 100 && gen->map_y < 100 && gen->on == 0)
	{
		draw_map_2d(data, W_WIDTH, W_HEIGHT, gen);
		draw_player(data, W_WIDTH, W_HEIGHT, gen);
	}
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, img_ptr, 0, 0);
	mlx_destroy_image(gen->mlx_ptr, img_ptr);
	return (0);
}
