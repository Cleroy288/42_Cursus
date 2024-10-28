/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:35:01 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/05 20:43:41 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "lib/libft.h"
# include "mini_lib/libx/mlx.h"
# include <stdio.h>

typedef struct s_map
{
	int		width;
	int		height;
	int		tile_width;
	int		tile_height;
	char	**data;
	int		tile_size;
}	t_map;

typedef struct s_need
{
	int		x;
	int		y;
}	t_need;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	int		img_with;
	int		img_height;
	int		sprite_width;
	int		sprite_height;
	void	*img_up1;
	void	*img_up2;
	void	*img_down1;
	void	*img_down2;
	void	*img_left1;
	void	*img_left2;
	void	*img_right1;
	void	*img_right2;
	void	*img_neutral;
	void	*mob;
	int		x_pos;
	int		y_pos;
	int		moving;
	int		animation_state;
	void	*pipe_image;
	t_map	*map;
	void	*bg_img;
	void	*wall_img;
	void	*collectible_img;
	void	*exit_img;
	void	*player_img;
	int		collectibles_count;
	int		key_press_count;
	void	*undesirable_win;
	int		move_ok;
	int		write_term;
}	t_mlx;

typedef struct s_image
{
	void	*img;
	int		*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_collision_data
{
	int		x;
	int		y;
	t_mlx	*st;
	int		offsetx;
	int		offsety;
	int		points_on_non_wall;
	int		i;
	int		tile_x;
	int		tile_y;
	int		tiles[9][2];
}	t_collision_data;

typedef struct s_subimg_params
{
	void	*mlx;
	void	*img;
	int		src_x;
	int		src_y;
	int		width;
	int		height;
	void	*sub_img;
	int		*src_data;
	int		*dst_data;
	int		bpp;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	t_mlx	*st;
}				t_subimg_params;

int		ft_is_valid_middel(char **map, int *exit, int *item, int *pos);
int		ft_is_valid_map(char **map, int nb);
int		ft_last_filepart_is(char *str, char *word);
int		ft_pathfinding(char **map, int itm, int x, int y);
void	handle_up(int step, t_mlx *st);
void	handle_down(int step, t_mlx *st);
void	handle_left(int step, t_mlx *st);
void	handle_right(int step, t_mlx *st);
int		is_player_on_exit(t_mlx *st);
int		is_wall(t_mlx *st, int x, int y);
int		ft_paint(t_mlx *st);
void	draw_key_press_count(t_mlx *st);
int		key_pressed(int keycode, t_mlx *st);
void	draw_collectibles_count(t_mlx *st);
void	*flip_image_horizontally(void *mlx, void *img, int width, int height);
void	ft_movement_and_management(t_mlx *st);
int		count_collectibles(t_map *map);
void	load_sub_images(t_mlx *st);
void	find_player_position(t_mlx *st, int *player_x, int *player_y);
t_map	*ft_create_map(char *map_path);
t_mlx	*init_mlx(char *map_path);
void	ft_draw_map(t_mlx *st, int x, int y);
char	**copy_map(char **map_real, int map_height, int map_width);
char	**ft_set_map_in_dubbel_str(int fd, int *num, char *map_path);

#endif
