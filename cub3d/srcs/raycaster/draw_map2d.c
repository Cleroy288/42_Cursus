/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:51:46 by charleslero       #+#    #+#             */
/*   Updated: 2023/10/14 13:51:52 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	fill_background(char *data, int width, t_gen *gen)
{
	int	y;
	int	x;
	int	index;

	y = 0;
	while (y < gen->map_y * gen->map_s / gen->scale_f)
	{
		x = 0;
		while (x < gen->map_x * gen->map_s / gen->scale_f)
		{
			index = (y + gen->offset_big_y) * width + (x + gen->offset_big_x);
			if (isvalidindex(index * 4, gen->total_size)
				&& isvalidindex(index * 4 + 2, gen->total_size))
			{
				data[index * 4] = 0x80;
				data[index * 4 + 1] = 0x80;
				data[index * 4 + 2] = 0x80;
			}
			x++;
		}
		y++;
	}
}

void	set_cell_color(t_gen *gen, int y, int x)
{
	if (gen->map->map_array[y][x] == '1')
		gen->color = 0xFFFFFF;
	else
		gen->color = 0x000000;
}

void	draw_cell(char *data, t_gen *gen, int x, int y)
{
	int	i;
	int	j;
	int	index;

	gen->pos_big_x = (x * gen->map_s / gen->scale_f) + gen->offset_big_x + 1;
	gen->pos_big_y = (y * gen->map_s / gen->scale_f) + gen->offset_big_y + 1;
	i = 0;
	while (i < gen->map_s / gen->scale_f - 2)
	{
		j = 0;
		while (j < gen->map_s / gen->scale_f - 2)
		{
			index = (gen->pos_big_y + j) * W_WIDTH + (gen->pos_big_x + i);
			if (isvalidindex(index * 4, gen->total_size)
				&& isvalidindex(index * 4 + 2, gen->total_size))
			{
				data[index * 4] = (gen->color & 0xFF);
				data[index * 4 + 1] = (gen->color >> 8) & 0xFF;
				data[index * 4 + 2] = (gen->color >> 16) & 0xFF;
			}
			j++;
		}
		i++;
	}
}

void	draw_map_2d(char *data, int width, int height, t_gen *gen)
{
	int	y;
	int	x;

	gen->total_size = width * height * 4;
	gen->offset_big_x = 10;
	gen->offset_big_y = 10;
	gen->scale_f = 4;
	fill_background(data, width, gen);
	y = 0;
	while (y < gen->map_y)
	{
		x = 0;
		while (x < gen->map_x)
		{
			set_cell_color(gen, y, x);
			draw_cell(data, gen, x, y);
			x++;
		}
		y++;
	}
}
