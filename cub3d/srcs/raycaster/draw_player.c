/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:51:54 by chleroy           #+#    #+#             */
/*   Updated: 2023/10/14 12:55:39 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	ft_init_draw_player_(int part, t_gen *gen)
{
	gen->scale_f = 4;
	if (part == 1)
	{
		gen->total_size = W_WIDTH * W_HEIGHT * 4;
		gen->scale_f = 4;
		gen->offset_big_x = 10;
		gen->offset_big_y = 10;
		gen->scaled_px = gen->px / gen->scale_f;
		gen->scaled_py = gen->py / gen->scale_f;
		gen->scaled_pdx = gen->pdx * 5 / gen->scale_f;
		gen->scaled_pdy = gen->pdy * 5 / gen->scale_f;
	}
	else
	{
		gen->center_big_x = gen->scaled_px + 2 / gen->scale_f;
		gen->center_big_y = gen->scaled_py + 2 / gen->scale_f;
		gen->line_big_x = gen->center_big_x + gen->scaled_pdx;
		gen->line_big_y = gen->center_big_y + gen->scaled_pdy;
	}
}

static void	init_gen_for_draw_player(t_gen *gen)
{
	gen->i = 0;
	gen->y = 0;
	gen->x = 0;
}

void	draw_player(char *data, int width, int height, t_gen *gen)
{
	init_gen_for_draw_player(gen);
	ft_init_draw_player_(1, gen);
	while (gen->y < 5 / gen->scale_f)
	{
		gen->x = 0;
		while (gen->x < 5 / gen->scale_f)
		{
			gen->i = (gen->scaled_py + gen->y + gen->offset_big_y) * width
				+ (gen->scaled_px + gen->x + gen->offset_big_x);
			if (isvalidindex(gen->i * 4, gen->total_size)
				&& isvalidindex(gen->i * 4 + 2, gen->total_size))
			{
				data[gen->i * 4] = 0;
				data[gen->i * 4 + 1] = 0;
				data[gen->i * 4 + 2] = (char)255;
			}
			gen->x++;
		}
		gen->y++;
	}
	ft_init_draw_player_(2, gen);
	gen->color = 0x00FF00;
	draw_line(width, data, height, gen);
}
