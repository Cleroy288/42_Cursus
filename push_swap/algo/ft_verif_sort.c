/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:35:58 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/15 15:36:44 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_verif_sort(t_push_swap *t_push_swap)
{
	long	i;

	i = 0;
	while (i < t_push_swap->len_stack_a - 1)
	{
		if (t_push_swap->stack_a[i] > t_push_swap->stack_a[i + 1])
			return (1);
		i++;
	}
	return (0);
}
