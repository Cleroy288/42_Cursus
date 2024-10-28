/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:02:36 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/03 16:10:21 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_last_filepart_is(char *str, char *word)
{
	size_t	len_str;
	size_t	len_word;

	if (str && word)
	{
		len_str = ft_strlen(str);
		len_word = ft_strlen(word);
		if (word[len_word] == str[len_str])
		{
			while (word[len_word] == str[len_str]
				&& len_word < ft_strlen(word) && len_str < ft_strlen(str))
			{
				len_str--;
				len_word--;
			}
			if (word[len_word] == '\0')
				return (1);
		}
	}
	return (0);
}

int	count_collectibles(t_map *map)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	if (!map)
		return (0);
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->data[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	find_player_position(t_mlx *st, int *player_x, int *player_y)
{
	int	y;
	int	x;

	y = 0;
	while (y < st->map->height)
	{
		x = 0;
		while (x < st->map->width)
		{
			if (st->map->data[y][x] == 'P')
			{
				*player_x = x;
				*player_y = y;
				break ;
			}
			x++;
		}
		y++;
	}
}
