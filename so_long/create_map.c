/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:37:57 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/06 11:14:54 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_draw_map(t_mlx *st, int x, int y)
{
	while (y < st->map->height)
	{
		x = 0;
		while (x < st->map->width - 1)
		{
			mlx_put_image_to_window(st->mlx, st->mlx_win, st->bg_img, x * st
				->map->tile_width, y * st->map->tile_height);
			if (st->map->data[y][x] == '1')
				mlx_put_image_to_window(st->mlx, st->mlx_win, st->wall_img,
					x * st->map->tile_width, y * st->map->tile_height);
			else if (st->map->data[y][x] == 'C')
				mlx_put_image_to_window(st->mlx, st->mlx_win, st
					->collectible_img, x * st->map->tile_width,
					y * st->map->tile_height);
			else if (st->map->data[y][x] == 'E')
				mlx_put_image_to_window(st->mlx, st->mlx_win, st->exit_img,
					x * st->map->tile_width, y * st->map->tile_height);
			else if (st->map->data[y][x] == 'M')
				mlx_put_image_to_window(st->mlx, st->mlx_win, st->mob,
					x * st->map->tile_width, y * st->map->tile_height);
			x++;
		}
		y++;
	}
}

void	load_images(t_mlx *st)
{
	int	img_width;
	int	img_height;

	img_width = 0;
	img_height = 0;
	st->bg_img = mlx_xpm_file_to_image(st->mlx, "./map_img/arriereplan.xpm",
			&img_width, &img_height);
	st->wall_img = mlx_xpm_file_to_image(st->mlx, "./map_img/new_tuyaux.xpm",
			&img_width, &img_height);
	st->collectible_img = mlx_xpm_file_to_image(st->mlx,
			"./map_img/liquide_portail.xpm",
			&img_width, &img_height);
	st->player_img = mlx_xpm_file_to_image(st->mlx, "./map_img/pickle.xpm",
			&img_width, &img_height);
	st->exit_img = mlx_xpm_file_to_image(st->mlx, "./map_img/new_exit.xpm",
			&img_width, &img_height);
	st->mob = mlx_xpm_file_to_image(st->mlx, "map_img/champi.xpm",
			&img_width, &img_height);
	if (!st->mob || !st->bg_img || !st->wall_img || !st->collectible_img
		|| !st->player_img || !st->exit_img)
		return (ft_putstr_fd("nop", 2));
}

t_mlx	*setup_mlx(t_mlx *st, char *map_path)
{
	int	player_x;
	int	player_y;

	(void)map_path;
	st->mlx_win = mlx_new_window(st->mlx, (st->map->width - 1) * st->map
			->tile_width, st->map->height * st->map->tile_height, "so long");
	load_images(st);
	find_player_position(st, &player_x, &player_y);
	st->x_pos = player_x * st->map->tile_width;
	st->y_pos = player_y * st->map->tile_height;
	st->img = mlx_xpm_file_to_image(st->mlx, "./map_img/pickle.xpm", &st
			->img_with, &st->img_height);
	if (!st->img)
	{
		ft_putstr_fd("Error: Failed to load XPM file.\n", 2);
		return (NULL);
	}
	st->sprite_width = st->img_with / 4;
	st->sprite_height = st->img_height / 3;
	load_sub_images(st);
	st->img = st->img_down1;
	st->animation_state = 0;
	st->moving = 0;
	return (st);
}

t_mlx	*init_mlx(char *map_path)
{
	t_mlx	*st;

	st = malloc(sizeof(t_mlx));
	if (!st)
		return (NULL);
	st->map = ft_create_map(map_path);
	if (!st->map)
		return (NULL);
	st->collectibles_count = count_collectibles(st->map);
	st->sprite_width = st->map->tile_width / 4;
	st->sprite_height = st->map->tile_height / 3;
	st->mlx = mlx_init();
	return (setup_mlx(st, map_path));
}

t_map	*ft_create_map(char *map_path)
{
	int		fd;
	int		nb;
	char	**map;
	t_map	*new_map;

	nb = 0;
	fd = open(map_path, O_RDONLY);
	map = ft_set_map_in_dubbel_str(fd, &nb, map_path);
	if (ft_is_valid_map(map, nb) == 0)
		return (NULL);
	new_map = (t_map *)malloc(sizeof(t_map));
	if (!new_map)
		return (NULL);
	new_map->width = ft_strlen(map[0]);
	new_map->height = nb;
	new_map->data = map;
	new_map->tile_width = 48;
	new_map->tile_height = 64;
	return (new_map);
}
