/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_through_screen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:51:50 by chleroy           #+#    #+#             */
/*   Updated: 2023/10/14 13:01:51 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	draw_floor(char *data, t_gen *gen)
{
	double		y;

	y = gen->line_b_o + gen->line_b_h;
	gen->data = &data;
	while (y < W_HEIGHT)
	{
		draw_rectangle_floor(gen, data, y, 1);
		y++;
	}
}

void	ft_init_values_for_draw_rays_3d(t_gen *gen, int width)
{
	gen->height = W_HEIGHT;
	gen->max_ray_dist = 10000;
	gen->scale_f = (long double)width / 1920.0;
	gen->ra = gen->pa - (30 * (PI / 180));
	if (gen->ra < 0)
		gen->ra += 2 * PI;
	if (gen->ra > 2 * PI)
		gen->ra -= 2 * PI;
	gen->ray_st_x = gen->px + 2.5;
	gen->ray_st_y = gen->py + 2.5;
	gen->r = 0;
}

void	correcte_fisheye(t_gen *gen)
{
	gen->ca = gen->pa - gen->ra;
	if (gen->ca < 0)
		gen->ca += 2 * PI;
	if (gen->ca > 2 * PI)
		gen->ca -= 2 * PI;
	gen->dis_t = gen->dis_t * cos(gen->ca);
}

void	ft_set_gen_rays_valuesfor_dish(t_gen *gen)
{
	gen->dis_h = 100000;
	gen->hx = gen->ray_st_x;
	gen->hy = gen->ray_st_y;
	gen->dof = 0;
	gen->a_tan = -1 / tan(gen->ra);
	if (gen->ra > PI)
	{
		gen->ry = (((int)gen->ray_st_y >> 6) << 6) - 0.0001;
		gen->rx = (gen->ray_st_y - gen->ry) * gen->a_tan + gen->ray_st_x;
		gen->yo = -64.0000000;
		gen->xo = -gen->yo * gen->a_tan;
	}
	else if (gen->ra < PI)
	{
		gen->ry = (((int)gen->ray_st_y >> 6) << 6) + 64;
		gen->rx = (gen->ray_st_y - gen->ry) * gen->a_tan + gen->ray_st_x;
		gen->yo = 64.0000000;
		gen->xo = -gen->yo * gen->a_tan;
	}
	else
	{
		gen->rx = gen->ray_st_x;
		gen->ry = gen->ray_st_y;
		gen->dof = 8;
	}
}

void	go_through_screen(t_gen *gen)
{
	while (gen->dof < gen->max_ray_dist)
	{
		gen->mx = (int)(gen->rx) >> 6;
		gen->my = (int)(gen->ry) >> 6;
		if (gen->my >= 0 && gen->my < gen->map_y && gen->mx >= 0
			&& gen->mx < gen->map_x
			&& gen->map->map_array[gen->my][gen->mx] == '1')
		{
			gen->hx = gen->rx;
			gen->hy = gen->ry;
			gen->dis_h = dis(gen->ray_st_x, gen->ray_st_y, gen->hx, gen->hy);
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
