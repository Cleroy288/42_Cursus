/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_val_to_tab_rank.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:12:00 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/19 10:12:02 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	*ft_change_val_tab_to_rank(long *tab, int nb_of_nb, t_push_swap *stack)
{
	long	i;
	long	j;
	long	rank;
	long	*tab_rank;

	tab_rank = malloc(sizeof(long) * nb_of_nb);
	if (!tab_rank)
		return (0);
	i = 0;
	while (i < nb_of_nb)
	{
		rank = 0;
		j = 0;
		while (j < nb_of_nb)
		{
			if (tab[j] < tab[i] || (tab[j] == tab[i] && j < i))
				rank++;
			j++;
		}
		tab_rank[i] = rank;
		i++;
	}
	free(stack->stack_a);
	stack->stack_a = tab_rank;
	return (tab_rank);
}
