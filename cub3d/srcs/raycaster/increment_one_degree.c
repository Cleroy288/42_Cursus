/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_one_degree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:47:26 by charleslero       #+#    #+#             */
/*   Updated: 2023/10/13 23:48:39 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	increment_ra_from_one_dgree(t_gen *gen)
{
	if (gen->ra < 0)
		gen->ra += 2 * PI;
	if (gen->ra > 2 * PI)
		gen->ra -= 2 * PI;
}
