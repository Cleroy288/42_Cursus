/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_and_determine_wall_texture.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:04:40 by chleroy           #+#    #+#             */
/*   Updated: 2023/10/14 12:58:48 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

int	get_pixel_color(t_texture *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->data + (y * texture->size_line + x * (texture->bpp / 8));
	return (*(int *)pixel);
}

void	draw_wall_texture(char *data, t_gen *gen)
{
	int			i;
	int			color;
	long int	pixel_x;
	long int	pixel_y;
	long int	index;

	i = 0;
	while (i < gen->line_b_h)
	{
		color = get_pixel_color(gen->wall_texture, gen->tex_x, (long int)
				(((long double)i / gen->line_b_h) * gen->wall_texture->height));
		pixel_x = gen->wall_big_x;
		pixel_y = gen->line_b_o + i;
		if (pixel_x >= 0 && pixel_x < W_WIDTH && pixel_y >= 0
			&& pixel_y < gen->height)
		{
			index = (pixel_y * W_WIDTH + pixel_x) * 4;
			data[index] = (color >> 16) & 0xFF;
			data[index + 1] = (color >> 8) & 0xFF;
			data[index + 2] = color & 0xFF;
		}
		i++;
	}
}

void	draw_rectangle(t_gen *gen, char *data, int y, long double rect_height)
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
				data[index] = (gen->ceiling_color >> 16) & 0xFF;
				data[index + 1] = (gen->ceiling_color >> 8) & 0xFF;
				data[index + 2] = gen->ceiling_color & 0xFF;
			}
			j++;
		}
		i++;
	}
}
