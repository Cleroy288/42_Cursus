/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:17:48 by charleslero       #+#    #+#             */
/*   Updated: 2023/10/14 13:01:51 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	print_all_x(int len)
{
	int	i;

	i = 0;
	printf("        ");
	while (i != len)
	{
		printf("%d ", i);
		i++;
	}
	printf("\n");
}

int	is_spawn(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (1);
	return (0);
}

void	print(char c)
{
	if (c == '1')
		printf("%c ", c);
	else if (c == '0')
		printf("%c ", c);
	else if (is_spawn(c) == 1)
		printf("%c ", c);
	else
		printf("  ");
}

void	ft_take_and_set_tp_adres(t_gen *gen)
{
	char	*y;
	char	*x;

	y = NULL;
	x = NULL;
	while (y == NULL)
		y = readline("enter y coordinates = ");
	while (x == NULL)
		x = readline("enter x coordinates = ");
	if (ft_atoi(y) < gen->map_y
		&& gen->map->map_array[ft_atoi(y)][ft_atoi(x)] == '0')
	{
		gen->px = ft_atoi(x) * gen->map_s + gen->map_s / 2;
		gen->py = ft_atoi(y) * gen->map_s + gen->map_s / 2;
	}
	else
		printf("c'mon man ...\n");
	free(x);
	free(y);
}

int	print_map_for_tp(t_gen *gen)
{
	int		i;
	int		j;
	char	**mp;

	i = 0;
	mp = gen->map->map_array;
	print_all_x(ft_strlen(mp[0]));
	while (mp[i])
	{
		j = 0;
		printf("y [%d] - ", i);
		while (mp[i][j])
		{
			print(mp[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
	ft_take_and_set_tp_adres(gen);
	return (0);
}
