/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:34:08 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/15 21:50:49 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../srcs/ft_printf/ft_printf.h"
# include "../srcs/libft/libft.h"
# include "../srcs/gnl/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "../mini_lib/libx/mlx.h"
# include <readline/readline.h>
# include <readline/history.h>

# define PI 3.141592653589793
# define DR 0.0174533
# define PLAYER_MARGIN 5.0
# define W_HEIGHT 1080
# define W_WIDTH 1200
# define SPEED 3
# define FIXED_WALL_HEIGHT 64;

/*** ~STRUCTS~ ***/

typedef struct s_map
{
	char				**map_array;
	struct s_textures	*textures;
}	t_map;

typedef struct s_textures
{
	char	*no_texture_path;
	char	*so_texture_path;
	char	*we_texture_path;
	char	*ea_texture_path;
	int		*f_color;
	int		*c_color;
}	t_textures;

typedef struct s_wall_hit
{
	long double	rx;
	long double	ry;
	long double	dist_b_t;
	long double	color;
}	t_wall_hit;

typedef enum t_move_dirs {
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT,
	TURN_LEFT,
	TURN_RIGHT
}	t_move_dir;

typedef struct t_collision_pt {
	long double	front_x;
	long double	front_y;
	long double	back_x;
	long double	back_y;
	long double	left_x;
	long double	left_y;
	long double	right_x;
	long double	right_y;
}	t_collision_pt;

typedef struct t_player_collision_points {
	long double	front_margin;
	long double	back_margin;
	long double	left_margin;
	long double	right_margin;
}	t_player_collision_points;

typedef struct s_texture {
	void	*img_ptr;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_gen {
	int			on;
	t_map		*map;

	void		*mlx_ptr;
	void		*win_ptr;

	long double	pdx;
	long double	pdy;
	long double	pa;
	long double	px;
	long double	py;
	int			map_y;
	int			map_x;
	int			map_s;
	int			move_forward;
	int			move_backward;
	int			turn_left;
	int			turn_right;
	int			move_left;
	int			move_right;

	long int	mx_front;
	long int	my_front;
	long int	mx_back;
	long int	my_back;
	long int	mx_left;
	long int	my_left;
	long int	mx_right;
	long int	my_right;

	long int	my;
	long int	mx;
	long double	mp;
	long double	dof;
	long double	r;
	long double	rx;
	long double	ry;
	long double	ra;
	long double	xo;
	long double	yo;
	long double	dis_t;

	int			height;
	int			max_ray_dist;
	long double	scale_f;
	long double	ray_st_x;
	long double	ray_st_y;
	t_wall_hit	wall_hit;

	t_texture	*north_texture;
	t_texture	*south_texture;
	t_texture	*east_texture;
	t_texture	*west_texture;

	long double	dis_h;
	long double	a_tan;

	t_texture	*wall_texture;
	long double	dis_v;
	long double	n_tan;
	int			color;
	long double	ca;
	long double	standartd_dist;
	long double	texture_height;
	long double	line_b_h;
	long double	line_b_o;
	long double	colum_width;
	long double	wall_big_x;
	long double	tex_x;

	int			floor_color_in_int;
	long double	adjusted_line_h;
	long double	adjusted_line_o;
	long double	floor_big_x;
	long double	floor_start_big_y;
	long double	floor_height;
	int			ceiling_color;
	long double	hx;
	long double	hy;
	long double	atan;
	long double	vx;
	long double	vy;

	int			total_size;

	int			offset_big_x;
	int			offset_big_y;
	int			scaled_px;
	int			scaled_py;
	int			scaled_pdx;
	int			scaled_pdy;

	int			center_big_x;
	int			center_big_y;

	int			line_big_x;
	int			line_big_y;

	int			x1;
	int			y1;
	int			x0;
	int			y0;
	int			dx;
	int			dy;
	int			err;
	int			sx;
	int			sy;
	int			e2;

	int			pos_big_x;
	int			pos_big_y;
	int			x;
	int			y;
	int			i;
	char		**data;
}	t_gen;

/*** ~DEFINES ***/

# define R 0
# define G 1
# define B 2

/*** ~ENUMS~ ***/

enum	e_tokens	{e_no, e_so, e_we, e_ea, e_f, e_c};

/*** ~PARSING~ ***/

void	parsing(t_map **map, char *map_path);
int		check_file(t_map **map, char *map_path);
char	**get_file_arr(t_map **map, int map_fd);
void	get_map_datas(t_map **map, char **file_arr);
void	get_map_arr(t_map **map, char **file_arr);
void	fix_map(t_map **map);
void	treat_line(t_map **map, char **file_arr, int i);
void	get_wall_texture(t_map **map, char **file_arr,
			char **tmp_arr, int type);
void	get_fc_color(t_map **map, char **file_arr, char **tmp_arr, int type);
char	**add_line_to_arr(t_map **map, char **file_arr, int i);
char	*trim_set(char *line, char *set);
void	parse_map(t_map **map);

/*** ~UTILS~ ***/

void	print_error_exit(t_map **map, char *str, int exit_code);
void	close_fd_and_pee(t_map **map, char *str, int exit_code, int fd);
t_map	*map_init(void);
void	free_map(t_map **map);
void	free_arr(void **str);
int		get_arr_size(void **arr);
bool	is_set(char c, char *set);
void	ca_malloc_fail_free(t_map **map, char **tmp_arr);
void	sl_malloc_fail_free(t_map **map, char **tmp_arr, int *color_arr);
bool	parse_color_line(char *line);
void	wrong_format_free(t_map **map, char **tmp_arr, int *color_arr);
void	*calloc_with_spaces(size_t count, size_t size);

//exec
int		isvalidindex(int index, int totalsize);
void	ft_init_draw_line_val(t_gen *gen);
void	ft_set_val_for_err_and_y0_and_e2(t_gen *gen);
float	dis(float ax, float ay, float bx, float by);
int		ft_calculate_right_color(int *rgb_values, t_gen *gen);
int		get_pixel_color(t_texture *texture, int x, int y);
void	draw_wall_texture(char *data, t_gen *gen);
void	draw_line(int width, char *data, int height, t_gen *gen);
void	draw_floor(char *data, t_gen *gen);
void	ft_init_values_for_draw_rays_3d(t_gen *gen, int width);
void	ft_set_gen_rays_valuesfor_disH(t_gen *gen);
void	go_through_screen(t_gen *gen);
void	ft_set_gen_rays_valuesfor_disv(t_gen *gen);
void	go_through_screen_2(t_gen *gen);
void	wich_wall_is_hit(t_gen *gen);
void	correcte_fisheye(t_gen *gen);
void	body_of_what_happens_for_drawing_walls(t_gen *gen, char *data);
void	body_of_what_happens_for_drawing_floor(t_gen *gen, char *data);
void	body_of_what_happens_to_draw_the_cieling(t_gen *gen, char *data);
void	increment_ra_from_one_dgree(t_gen *gen);
void	free_textures(t_gen *gen);
void	other_drawrays3D(char *data, int width, t_gen *gen);
void	ft_init_draw_player_(int part, t_gen *gen);
void	draw_player(char *data, int width, int height, t_gen *gen);
void	fill_background(char *data, int width, t_gen *gen);
void	set_cell_color(t_gen *gen, int y, int x);
void	draw_cell(char *data, t_gen *gen, int x, int y);
void	draw_map_2d(char *data, int width, int height, t_gen *gen);
int		key_release(int key, t_gen *gen);
int		close_program(t_gen *gen);
int		key_press(int key, t_gen *gen);
int		is_wall(char cell);
void	ft_init_can_move_values(float new_x, float new_y,
			t_gen *gen, t_player_collision_points pc);
int		is_any_wall(t_gen *gen);
int		can_move(float new_x, float new_y, t_move_dir direction, t_gen *gen);
void	move_forward(t_gen *gen);
void	move_backward(t_gen *gen);
void	turn_left(t_gen *gen);
void	turn_right(t_gen *gen);
void	move_left(t_gen *gen);
void	move_right(t_gen *gen);
void	ft_moves(t_gen *gen);
int		refresh(t_gen *gen);
void	ft_print_2d_array(char **r);
void	set_player_angle(t_gen *gen, char tile);
int		ft_len_2d_tab(char **s);
void	init_player_starting_position(t_gen *gen);
void	ft_init_gen(t_gen *gen, t_map *mapp);
int		start_of_execution(t_map *mapp);
void	other_drawrays3d(char *data, int width, t_gen *gen);
void	ft_set_gen_rays_valuesfor_dish(t_gen *gen);
void	draw_rectangle_floor(t_gen *gen, char *data,
			int y, long double rect_height);
void	draw_rectangle(t_gen *gen, char *data, int y, long double rect_height);
void	ft_load_textures(t_gen *gen);
int		print_map_for_tp(t_gen *gen);

size_t	not_null_terminated_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
