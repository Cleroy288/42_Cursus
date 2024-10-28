/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_gen_rays_disv.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 00:17:54 by charleslero       #+#    #+#             */
/*   Updated: 2023/10/14 13:51:07 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	ft_set_gen_rays_valuesfor_disv(t_gen *gen)
{
	gen->dis_v = 100000;
	gen->vx = gen->ray_st_x;
	gen->vy = gen->ray_st_y;
	gen->dof = 0;
	gen->n_tan = -tan(gen->ra);
	if (gen->ra > PI / 2 && gen->ra < 3 * PI / 2)
	{
		gen->rx = (((int)gen->ray_st_x >> 6) << 6) - 0.0001;
		gen->ry = (gen->ray_st_x - gen->rx) * gen->n_tan + gen->ray_st_y;
		gen->xo = -1.0000000;
		gen->yo = -gen->xo * gen->n_tan;
	}
	else if (gen->ra < PI / 2 || gen->ra > 3 * PI / 2)
	{
		gen->rx = (((int)gen->ray_st_x >> 6) << 6) + 64;
		gen->ry = (gen->ray_st_x - gen->rx) * gen->n_tan + gen->ray_st_y;
		gen->xo = 1.00000000;
		gen->yo = -gen->xo * gen->n_tan;
	}
	else
	{
		gen->rx = gen->ray_st_x;
		gen->ry = gen->ray_st_y;
		gen->dof = 8;
	}
}
