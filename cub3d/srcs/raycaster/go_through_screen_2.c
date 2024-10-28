/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_through_screen_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:51:54 by charleslero       #+#    #+#             */
/*   Updated: 2023/10/14 13:01:51 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	go_through_screen_2(t_gen *gen)
{
	while (gen->dof < gen->max_ray_dist)
	{
		gen->mx = (int)(gen->rx) >> 6;
		gen->my = (int)(gen->ry) >> 6;
		if (gen->my >= 0 && gen->my < gen->map_y && gen->mx >= 0
			&& gen->mx < gen->map_x
			&& gen->map->map_array[gen->my][gen->mx] == '1')
		{
			gen->vx = gen->rx;
			gen->vy = gen->ry;
			gen->dis_v = dis(gen->ray_st_x, gen->ray_st_y, gen->vx, gen->vy);
			gen->dof = gen->max_ray_dist;
		}
		else
		{
			gen->rx += gen->xo;
			gen->ry += gen->yo;
			gen->dof += 1;
		}
	}
}
