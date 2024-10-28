/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:28:38 by chleroy           #+#    #+#             */
/*   Updated: 2023/10/14 13:54:58 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

t_wall_hit	determine_wall_hit(t_gen *gen)
{
	t_wall_hit	result;

	if (gen->dis_v < gen->dis_h)
	{
		result.rx = gen->vx;
		result.ry = gen->vy;
		result.dist_b_t = gen->dis_v;
		result.color = 0xFF0000;
	}
	else
	{
		result.rx = gen->hx;
		result.ry = gen->hy;
		result.dist_b_t = gen->dis_h;
		result.color = 0x990000;
	}
	return (result);
}

void	wich_wall_is_hit(t_gen *gen)
{
	gen->wall_hit = determine_wall_hit(gen);
	gen->rx = gen->wall_hit.rx;
	gen->ry = gen->wall_hit.ry;
	gen->dis_t = gen->wall_hit.dist_b_t;
	gen->color = gen->wall_hit.color;
}

t_texture	*determine_wall_texture(float disV,
	float disH, float ra, t_gen *gen)
{
	if (disV < disH)
	{
		if (ra > PI / 2 && ra < 3 * PI / 2)
			return (gen->east_texture);
		else
			return (gen->west_texture);
	}
	else
	{
		if (ra > PI)
			return (gen->north_texture);
		else
			return (gen->south_texture);
	}
}

long double	calculate_texture_x(long double disV,
	long double disH, long double vy, long double hx)
{
	if (disV < disH)
		return (((int)vy) % 64);
	else
		return (((int)hx) % 64);
}

void	body_of_what_happens_for_drawing_walls(t_gen *gen, char *data)
{
	gen->standartd_dist = 64.000000;
	gen->texture_height = 64.000000;
	gen->line_b_h = gen->scale_f
		* (((gen->map_s + 20) * gen->height) / gen->dis_t
			+ (gen->texture_height * gen->standartd_dist) / gen->dis_t);
	gen->line_b_o = (gen->height / 2) - (gen->line_b_h / 2);
	gen->colum_width = 1;
	gen->wall_big_x = gen->r * gen->colum_width;
	gen->wall_texture
		= determine_wall_texture(gen->dis_v, gen->dis_h, gen->ra, gen);
	gen->tex_x = calculate_texture_x(gen->dis_v, gen->dis_h, gen->vy, gen->hx);
	draw_wall_texture(data, gen);
}
