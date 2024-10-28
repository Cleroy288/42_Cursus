/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 10:26:01 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/06 11:20:57 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	**ft_set_map_in_dubbel_str(int fd, int *num, char *map_path)
{
	char	**map;
	int		i;

	(void)map_path;
	i = 0;
	if (!fd || fd == -1 || !num)
		return (NULL);
	map = malloc(sizeof(char *) * (153));
	if (!map)
	{
		free(map);
		return (NULL);
	}
	while (1)
	{
		map[i] = get_next_line(fd);
		if (map[i] == NULL)
			break ;
		i++;
	}
	*num = i;
	return (map);
}

int	ft_str_is(char *str, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	if (!str || !len)
		return (0);
	while (i < len - 1 && str[i])
	{
		if (str[i] != c && str[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_valid_map_form(char **map, size_t len, int nb)
{
	int	i;

	i = 1;
	if (!map)
		return (0);
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if ((len != ft_strlen(map[i - 1]) && i != nb - 1))
			return (0);
		i++;
	}
	if (ft_strlen(map[0]) == ft_strlen(map[nb - 1]) + 1)
		return (1);
	return (0);
}

int	ft_is_valid_middel(char **map, int *exit, int *item, int *pos)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (map[++i])
	{
		len = ft_strlen(map[i]);
		j = -1;
		if (map[i][0] != '1' && map[i][len] != '1')
			return (0);
		while (++j < len)
		{
			if (map[i][j] == 'P')
				*pos += 1;
			else if (map[i][j] == 'C')
				*item += 1;
			else if (map[i][j] == 'E')
				*exit += 1;
		}
	}
	if (*exit != 1 || *item == 0 || *pos != 1)
		return (0);
	return (1);
}

int	ft_is_valid_map(char **map, int nb)
{
	int		exit;
	int		item;
	int		pos;
	size_t	len;
	char	**map_cpy;

	pos = 0;
	exit = 0;
	item = 0;
	len = 0;
	if (ft_is_valid_map_form(map, len, nb) == 0)
		return (0);
	map_cpy = copy_map(map, nb, ft_strlen(map[0]));
	if (!map)
		return (0);
	if (ft_str_is(map[0], '1') != 1 || ft_str_is(map[nb - 1], '1') != 1)
		return (0);
	if (ft_is_valid_middel(map, &exit, &item, &pos) != 1)
		return (0);
	if (ft_pathfinding(map_cpy, item, 1, 1) == -1)
		return (0);
	return (1);
}
