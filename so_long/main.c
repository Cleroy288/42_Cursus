/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:51:28 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/06 11:15:59 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_mlx *st)
{
	mlx_destroy_window(st->mlx, st->mlx_win);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	*st;

	if (argc == 2 && ft_last_filepart_is(argv[1], ".ber"))
	{
		st = init_mlx(argv[1]);
		if (!st)
		{
			ft_putstr_fd("Error: Failed to initialize the game.\n", 2);
			return (1);
		}
		st->key_press_count = 0;
		ft_draw_map(st, 0, 0);
		mlx_hook(st->mlx_win, 2, 1L << 0, key_pressed, st);
		mlx_hook(st->mlx_win, 17, 1L << 17, close_window, st);
		st->collectibles_count = count_collectibles(st->map);
		ft_movement_and_management(st);
		mlx_loop(st->mlx);
	}
	else
		ft_putstr_fd("Error: Please provide '.ber' map extension.\n", 2);
	return (0);
}
