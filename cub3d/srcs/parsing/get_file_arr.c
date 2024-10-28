/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noloupe <noloupe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:33:01 by noloupe           #+#    #+#             */
/*   Updated: 2023/10/03 14:08:10 by noloupe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

char	*clear_file(t_map **map, char *file)
{
	char	*new;

	new = trim_set(file, "\011\13\014\015");
	free(file);
	if (!new)
		print_error_exit(map, "Malloc failed\n", EXIT_FAILURE);
	return (new);
}

char	**get_file_arr(t_map **map, int map_fd)
{
	char	*line;
	char	*file;
	char	**split_file;

	file = ft_strdup("");
	if (!file)
		close_fd_and_pee(map, "Malloc failed\n", EXIT_FAILURE, map_fd);
	line = get_next_line(map_fd);
	while (line)
	{
		file = strjoin_free_both(file, line);
		if (!file)
			close_fd_and_pee(map, "Malloc failed\n", EXIT_FAILURE, map_fd);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	file = clear_file(map, file);
	split_file = ft_split(file, '\n');
	if (!split_file)
	{
		free(file);
		print_error_exit(map, "Malloc failed\n", EXIT_FAILURE);
	}
	free(file);
	return (split_file);
}
