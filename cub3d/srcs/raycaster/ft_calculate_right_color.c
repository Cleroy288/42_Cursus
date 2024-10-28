/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_right_color.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 00:09:54 by charleslero       #+#    #+#             */
/*   Updated: 2023/10/14 13:52:13 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

int	ft_calculate_right_color(int *rgb_values, t_gen *gen)
{
	int	rgb;
	int	color_value;

	rgb = (rgb_values[0] << 16) | (rgb_values[1] << 8) | rgb_values[2];
	color_value = mlx_get_color_value(gen->mlx_ptr, rgb);
	return (color_value);
}
