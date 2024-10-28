/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:40:23 by chleroy           #+#    #+#             */
/*   Updated: 2023/10/14 00:09:52 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	ft_set_val_for_err_and_y0_and_e2(t_gen *gen)
{
	gen->e2 = gen->err;
	if (gen->e2 > -gen->dx)
	{
		gen->err -= gen->dy;
		gen->x0 += gen->sx;
	}
	if (gen->e2 < gen->dy)
	{
		gen->err += gen->dx;
		gen->y0 += gen->sy;
	}
}

void	draw_line(int width, char *data, int height, t_gen *gen)
{
	int	totalsize;
	int	i;

	ft_init_draw_line_val(gen);
	totalsize = width * height * 4;
	while (1)
	{
		i = gen->y0 * width + gen->x0;
		if (isvalidindex(i * 4, totalsize)
			&& isvalidindex(i * 4 + 2, totalsize))
		{
			data[i * 4] = (gen->color & 0xFF);
			data[i * 4 + 1] = (gen->color >> 8) & 0xFF;
			data[i * 4 + 2] = (gen->color >> 16) & 0xFF;
		}
		if (gen->x0 == gen->x1 && gen->y0 == gen->y1)
			break ;
		ft_set_val_for_err_and_y0_and_e2(gen);
	}
}

float	dis(float ax, float ay, float bx, float by)
{
	return (sqrtf((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

t_texture	*load_texture(void *mlx_ptr, char *path)
{
	t_texture	*texture;

	texture = (t_texture *)malloc(sizeof(t_texture));
	if (!texture)
	{
		printf("no texture 1\n");
		return (NULL);
	}
	texture->img_ptr = mlx_xpm_file_to_image(mlx_ptr,
			path, &texture->width, &texture->height);
	if (!texture->img_ptr)
	{
		printf("no texture 2 \n");
		free(texture);
		return (NULL);
	}
	texture->data = mlx_get_data_addr(texture->img_ptr,
			&texture->bpp, &texture->size_line, &texture->endian);
	if (!texture->data)
	{
		printf("no texture 3 \n");
		free(texture);
		return (NULL);
	}
	return (texture);
}

void	ft_load_textures(t_gen *gen)
{
	gen->north_texture = load_texture(gen->mlx_ptr,
			gen->map->textures->no_texture_path);
	gen->south_texture = load_texture(gen->mlx_ptr,
			gen->map->textures->so_texture_path);
	gen->east_texture = load_texture(gen->mlx_ptr,
			gen->map->textures->ea_texture_path);
	gen->west_texture = load_texture(gen->mlx_ptr,
			gen->map->textures->we_texture_path);
	if (!gen->north_texture || !gen->south_texture
		|| !gen->east_texture || !gen->west_texture)
	{
		printf("textures out\n");
		close_program(gen);
	}
}
