/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_val_line_val.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:55:02 by chleroy           #+#    #+#             */
/*   Updated: 2023/10/14 12:44:30 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	draw_rectangle_floor(t_gen *gen,
		char *data, int y, long double rect_height)
{
	int		i;
	int		j;
	double	p_x;
	double	p_y;
	int		index;

	i = 0;
	while (i < rect_height)
	{
		j = 0;
		while (j < gen->colum_width)
		{
			p_x = gen->wall_big_x + j;
			p_y = y + i;
			if (p_x >= 0 && p_x < W_WIDTH && p_y >= 0 && p_y < W_HEIGHT)
			{
				index = (p_y * W_WIDTH + p_x) * 4;
				data[index] = (gen->floor_color_in_int >> 16) & 0xFF;
				data[index + 1] = (gen->floor_color_in_int >> 8) & 0xFF;
				data[index + 2] = gen->floor_color_in_int & 0xFF;
			}
			j++;
		}
		i++;
	}
}

int	isvalidindex(int index, int totalsize)
{
	return (index >= 0 && index < totalsize);
}

void	ft_init_draw_line_val(t_gen *gen)
{
	gen->x0 = gen->center_big_x + gen->offset_big_x;
	gen->y0 = gen->center_big_y + gen->offset_big_y;
	gen->x1 = gen->line_big_x + gen->offset_big_x;
	gen->y1 = gen->line_big_y + gen->offset_big_y;
	gen->dx = abs(gen->x1 - gen->x0);
	gen->dy = abs(gen->y1 - gen->y0);
	if (gen->x0 < gen->x1)
		gen->sx = 1;
	else
		gen->sx = -1;
	if (gen->y0 < gen->y1)
		gen->sy = 1;
	else
		gen->sy = -1;
	if (gen->dx > gen->dy)
		gen->err = gen->dx / 2;
	else
		gen->err = -gen->dy / 2;
}
