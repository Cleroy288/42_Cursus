/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_images_and_counters.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:10:55 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/06 11:17:53 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_collectibles_count(t_mlx *st)
{
	char	*count_str;
	char	*text;

	count_str = ft_itoa(st->collectibles_count);
	if (st->collectibles_count != 0)
	{
		text = ft_strjoin("Collectibles: you cannot leave =>", count_str);
		mlx_string_put(st->mlx, st->mlx_win,
			st->map->width * st->map->tile_width - 300, 10, 0xFFFFFF, text);
	}
	if (st->collectibles_count == 0)
	{
		text = ft_strjoin("Collectibles: ZERRO you leave =>", count_str);
		mlx_string_put(st->mlx, st->mlx_win,
			st->map->width * st->map->tile_width - 300, 10, 0xFFFFFF, text);
	}
	free(count_str);
	free(text);
}

void	draw_key_press_count(t_mlx *st)
{
	char	*count_str;
	char	*text;

	count_str = ft_itoa(st->key_press_count / 2);
	text = ft_strjoin("Key Presses: ", count_str);
	mlx_string_put(st->mlx, st->mlx_win,
		st->map->width * st->map->tile_width - 300, 30, 0xFFFFFF, text);
	free(count_str);
	free(text);
}

int	ft_paint(t_mlx *st)
{
	mlx_clear_window(st->mlx, st->mlx_win);
	ft_draw_map(st, 0, 0);
	mlx_put_image_to_window(st->mlx,
		st->mlx_win, st->img, st->x_pos, st->y_pos);
	draw_collectibles_count(st);
	draw_key_press_count(st);
	return (0);
}

void	*ft_sub_i(void *mlx, int src_x, int src_y, t_subimg_params *params)
{
	params->sub_img = mlx_new_image(mlx, params->st->sprite_width,
			params->st->sprite_height);
	params->dst_data = (int *)mlx_get_data_addr(params->sub_img, &params->bpp,
			&params->size_line, &params->endian);
	params->src_data = (int *)mlx_get_data_addr(params->st->img, &params->bpp,
			&params->size_line, &params->endian);
	params->y = 0;
	while (params->y < params->st->sprite_height)
	{
		params->x = 0;
		while (params->x < params->st->sprite_width)
		{
			params->dst_data[params->y * params->st->sprite_width + params
				->x] = params->src_data[(src_y + params->y)
				* params->size_line / 4 + (src_x + params->x)];
			params->x++;
		}
		params->y++;
	}
	return (params->sub_img);
}

void	load_sub_images(t_mlx *st)
{
	t_subimg_params	params;

	params.st = st;
	st->img_up1 = ft_sub_i(st->mlx, 0 * st->sprite_width, 2 * st
			->sprite_height, &params);
	st->img_up2 = ft_sub_i(st->mlx, 1 * st->sprite_width, 2 * st
			->sprite_height, &params);
	st->img_neutral = ft_sub_i(st->mlx, 0 * st->sprite_width, 0 * st
			->sprite_height, &params);
	st->img_down1 = ft_sub_i(st->mlx, 1 * st->sprite_width, 0 * st
			->sprite_height, &params);
	st->img_down2 = ft_sub_i(st->mlx, 3 * st->sprite_width, 0 * st
			->sprite_height, &params);
	st->img_left1 = ft_sub_i(st->mlx, 0 * st->sprite_width, 1 * st
			->sprite_height, &params);
	st->img_left2 = ft_sub_i(st->mlx, 1 * st->sprite_width, 1 * st
			->sprite_height, &params);
	st->img_right1 = flip_image_horizontally(st->mlx, st->img_left1, st
			->sprite_width, st->sprite_height);
	st->img_right2 = flip_image_horizontally(st->mlx, st->img_left2, st
			->sprite_width, st->sprite_height);
}
