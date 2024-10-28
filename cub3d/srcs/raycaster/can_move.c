/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:52:00 by chleroy           #+#    #+#             */
/*   Updated: 2023/10/14 13:51:24 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

int	is_wall(char cell)
{
	if (cell != '0' && cell != 'N' && cell != 'E' && cell != 'W' && cell != 'S')
		return (1);
	else
		return (0);
}

t_player_collision_points	init_player_collision(void)
{
	t_player_collision_points	pc;
	float						val;

	val = 2;
	pc.front_margin = PLAYER_MARGIN - val;
	pc.back_margin = PLAYER_MARGIN - val;
	pc.left_margin = PLAYER_MARGIN - val;
	pc.right_margin = PLAYER_MARGIN - val;
	return (pc);
}

void	ft_init_can_move_values(float new_x,
	float new_y, t_gen *gen, t_player_collision_points pc)
{
	gen->mx_front = (new_x + gen->pdx * pc.front_margin) / gen->map_s;
	gen->my_front = (new_y + gen->pdy * pc.front_margin) / gen->map_s;
	gen->mx_back = (new_x - gen->pdx * pc.back_margin) / gen->map_s;
	gen->my_back = (new_y - gen->pdy * pc.back_margin) / gen->map_s;
	gen->mx_left = (new_x - gen->pdy * pc.left_margin) / gen->map_s;
	gen->my_left = (new_y + gen->pdx * pc.left_margin) / gen->map_s;
	gen->mx_right = (new_x + gen->pdy * pc.right_margin) / gen->map_s;
	gen->my_right = (new_y - gen->pdx * pc.right_margin) / gen->map_s;
}

int	is_any_wall(t_gen *gen)
{
	return (is_wall(gen->map->map_array[gen->my_front][gen->mx_front])
		|| is_wall(gen->map->map_array[gen->my_left][gen->mx_left])
		|| is_wall(gen->map->map_array[gen->my_right][gen->mx_right]));
}

int	can_move(float new_x, float new_y, t_move_dir direction, t_gen *gen)
{
	t_player_collision_points	pc;

	pc = init_player_collision();
	ft_init_can_move_values(new_x, new_y, gen, pc);
	if (direction == MOVE_FORWARD && is_any_wall(gen))
		return (0);
	if (direction == MOVE_BACKWARD && is_any_wall(gen))
		return (0);
	if (direction == MOVE_LEFT && is_any_wall(gen))
		return (0);
	if (direction == MOVE_RIGHT && is_any_wall(gen))
		return (0);
	if ((direction == TURN_LEFT || direction == TURN_RIGHT) && is_any_wall(gen))
		return (0);
	return (1);
}
