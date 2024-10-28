/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:51:37 by chleroy           #+#    #+#             */
/*   Updated: 2023/10/14 13:27:50 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	move_forward(t_gen *gen)
{
	float	new_x;
	float	new_y;

	new_x = gen->px + gen->pdx * (SPEED / 5.0);
	new_y = gen->py + gen->pdy * (SPEED / 5.0);
	if (can_move(new_x, new_y, MOVE_FORWARD, gen))
	{
		gen->px = new_x;
		gen->py = new_y;
	}
}

void	move_backward(t_gen *gen)
{
	float	new_x;
	float	new_y;

	new_x = gen->px - gen->pdx * (SPEED / 5.0);
	new_y = gen->py - gen->pdy * (SPEED / 5.0);
	if (can_move(new_x, new_y, MOVE_BACKWARD, gen))
	{
		gen->px = new_x;
		gen->py = new_y;
	}
}

void	turn_left(t_gen *gen)
{
	if (can_move(gen->px, gen->py, TURN_LEFT, gen))
	{
		gen->pa -= 0.1;
		if (gen->pa < 0)
			gen->pa += 2 * PI;
		gen->pdx = cos(gen->pa) * 5;
		gen->pdy = sin(gen->pa) * 5;
	}
}

void	turn_right(t_gen *gen)
{
	if (can_move(gen->px, gen->py, TURN_RIGHT, gen))
	{
		gen->pa += 0.1;
		if (gen->pa > 2 * PI)
			gen->pa -= 2 * PI;
		gen->pdx = cos(gen->pa) * 5;
		gen->pdy = sin(gen->pa) * 5;
	}
}
