/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:35:32 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/13 17:23:42 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
		print_error_exit(NULL, "Wrong number or arguments\n", EXIT_FAILURE);
	map = map_init();
	parsing(&map, argv[1]);
	start_of_execution(map);
	free_map(&map);
	//system("lsof | grep 'Cub3D'"); // tmp to check open FDs.
	return (0);
}
