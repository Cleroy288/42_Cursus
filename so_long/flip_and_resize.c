/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flip_and_resize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:45:41 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/03 17:09:32 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flip_image_data(t_image *src, t_image *dst)
{
	int	x;
	int	y;

	y = 0;
	while (y < dst->height)
	{
		x = 0;
		while (x < dst->width)
		{
			dst->data[y * dst->width + x] = src
				->data[y * src->width + (src->width - 1 - x)];
			x++;
		}
		y++;
	}
}

void	*flip_image_horizontally(void *mlx, void *img, int width, int height)
{
	t_image	src;
	t_image	dst;

	src.img = img;
	src.width = width;
	src.height = height;
	dst.img = mlx_new_image(mlx, width, height);
	dst.width = width;
	dst.height = height;
	src.data = (int *)mlx_get_data_addr(src.img, &src.bpp,
			&src.size_line, &src.endian);
	dst.data = (int *)mlx_get_data_addr(dst.img, &dst.bpp,
			&dst.size_line, &dst.endian);
	flip_image_data(&src, &dst);
	return (dst.img);
}
