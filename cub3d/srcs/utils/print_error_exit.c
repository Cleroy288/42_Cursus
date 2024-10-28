/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:31:46 by noloupe           #+#    #+#             */
/*   Updated: 2023/09/29 15:04:47 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	print_error_exit(t_map **map, char *str, int exit_code)
{
	if (map)
		free_map(map);
	ft_printf(2, "Error\n%s", str);
	exit(exit_code);
}

void	close_fd_and_pee(t_map **map, char *str, int exit_code, int fd)
{
	close(fd);
	print_error_exit(map, str, exit_code);
}
