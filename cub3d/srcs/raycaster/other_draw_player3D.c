/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_draw_player3D.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:51:19 by chleroy           #+#    #+#             */
/*   Updated: 2023/10/15 14:22:26 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	body_of_what_happens_for_drawing_floor(t_gen *gen, char *data)
{
	gen->floor_color_in_int
		= ft_calculate_right_color(gen->map->textures->f_color, gen);
	gen->adjusted_line_h = (int)(gen->line_b_h + 1);
	gen->adjusted_line_o = (int)(gen->line_b_o - 1);
	gen->floor_big_x = gen->r * W_WIDTH / 60;
	gen->floor_start_big_y = gen->line_b_o + gen->line_b_h;
	gen->floor_height = gen->height - gen->floor_start_big_y;
	draw_floor(data, gen);
}

void	body_of_what_happens_to_draw_the_cieling(t_gen *gen, char *data)
{
	gen->ceiling_color
		= ft_calculate_right_color(gen->map->textures->c_color, gen);
	gen->data = &data;
	draw_rectangle(gen, data, 0, gen->adjusted_line_o);
	gen->ra += (60 * (PI / 180)) / W_WIDTH;
}

void	free_textures(t_gen *gen)
{
	free(gen->north_texture);
	free(gen->south_texture);
	free(gen->east_texture);
	free(gen->west_texture);
}

void	other_drawrays3d(char *data, int width, t_gen *gen)
{
	ft_init_values_for_draw_rays_3d(gen, width);
	while (gen->r < width)
	{
		ft_set_gen_rays_valuesfor_dish(gen);
		go_through_screen(gen);
		ft_set_gen_rays_valuesfor_disv(gen);
		go_through_screen_2(gen);
		wich_wall_is_hit(gen);
		correcte_fisheye(gen);
		body_of_what_happens_for_drawing_walls(gen, data);
		body_of_what_happens_for_drawing_floor(gen, data);
		body_of_what_happens_to_draw_the_cieling(gen, data);
		increment_ra_from_one_dgree(gen);
		gen->r++;
	}
}
