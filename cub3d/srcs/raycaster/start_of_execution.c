/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_of_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:54:11 by chleroy           #+#    #+#             */
/*   Updated: 2023/10/14 13:01:51 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

int	mouse_move(int x, int y, t_gen *gen)
{
	static int	prev_x = W_WIDTH / 2;
	int			diff_x;
	int			left_threshold;
	int			right_threshold;

	(void)y;
	diff_x = x - prev_x;
	left_threshold = 10;
	right_threshold = W_WIDTH - 10;
	if (x > left_threshold && x < right_threshold)
	{
		gen->pa += diff_x * 0.005;
		if (gen->pa < 0)
			gen->pa += 2 * PI;
		if (gen->pa > 2 * PI)
			gen->pa -= 2 * PI;
		prev_x = x;
	}
	return (0);
}

void	ft_print_2d_array(char **r)
{
	int	i;

	i = 0;
	while (r[i])
	{
		printf("%s\n", r[i]);
		i++;
	}
}

void	ft_init_gen(t_gen *gen, t_map *mapp)
{
	gen->px = 64;
	gen->py = 64;
	gen->map_y = 7;
	gen->map_x = 8;
	gen->map_s = 64;
	gen->move_forward = 0;
	gen->move_backward = 0;
	gen->turn_left = 0;
	gen->turn_right = 0;
	gen->move_left = 0;
	gen->move_right = 0;
	gen->map = mapp;
}

int	start_of_execution(t_map *mapp)
{
	t_gen	*gen;

	gen = malloc(sizeof(t_gen));
	if (!gen)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_init_gen(gen, mapp);
	gen->on = 0;
	ft_print_2d_array(mapp->map_array);
	gen->mlx_ptr = mlx_init();
	gen->win_ptr = mlx_new_window(gen->mlx_ptr, W_WIDTH, W_HEIGHT, "cub3d");
	init_player_starting_position(gen);
	ft_load_textures(gen);
	gen->pdx = cos(gen->pa) * 5;
	gen->pdy = sin(gen->pa) * 5;
	mlx_hook(gen->win_ptr, 2, 1L << 0, key_press, gen);
	mlx_hook(gen->win_ptr, 3, 1L << 1, key_release, gen);
	mlx_hook(gen->win_ptr, 6, 1L << 6, mouse_move, gen);
	mlx_hook(gen->win_ptr, 17, 1L << 17, close_program, gen);
	mlx_loop_hook(gen->mlx_ptr, refresh, gen);
	mlx_loop(gen->mlx_ptr);
	return (0);
}
