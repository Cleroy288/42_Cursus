/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:51:43 by chleroy           #+#    #+#             */
/*   Updated: 2023/10/15 12:18:37 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

int	key_release(int key, t_gen *gen)
{
	if (key == 126 || key == 13)
		gen->move_forward = 0;
	if (key == 125 || key == 1)
		gen->move_backward = 0;
	if (key == 123)
		gen->turn_left = 0;
	if (key == 124)
		gen->turn_right = 0;
	if (key == 2)
		gen->move_left = 0;
	if (key == 0)
		gen->move_right = 0;
	return (0);
}

int	close_program(t_gen *gen)
{
	mlx_destroy_window(gen->mlx_ptr, gen->win_ptr);
	free_textures(gen);
	free(gen);
	exit(0);
}

void	exec_key(int key, t_gen *gen)
{
	if (key == 126 || key == 13)
		gen->move_forward = 1;
	if (key == 125 || key == 1)
		gen->move_backward = 1;
	if (key == 123)
		gen->turn_left = 1;
	if (key == 124)
		gen->turn_right = 1;
	if (key == 2)
		gen->move_left = 1;
	if (key == 0)
		gen->move_right = 1;
	if (key == 17 && gen->map_x < 100 && gen->map_y < 100)
		print_map_for_tp(gen);
}

int	key_press(int key, t_gen *gen)
{
	printf("pressed key: %d\n", key);
	if (key == 65307 || key == 53)
		close_program(gen);
	if (key == 15)
	{
		if (gen->on == 1)
			gen->on = 0;
		else if (gen->on == 0)
			gen->on = 1;
	}
	exec_key(key, gen);
	return (0);
}
