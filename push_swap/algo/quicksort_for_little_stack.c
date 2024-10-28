/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_for_little_stack.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:37:25 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/18 22:15:16 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_quick_sort_2(t_push_swap *stack)
{
	if (stack->nb == 2)
	{
		if (stack->stack_a[0] > stack->stack_a[1])
			ft_sa(stack);
	}
}

void	find_min_max(t_push_swap *stack, int *min, int *max)
{
	int	i;

	i = 0;
	*min = INT32_MAX;
	*max = INT32_MIN;
	while (i < stack->len_stack_a)
	{
		if ((int)(stack->stack_a[i]) > *max)
			*max = (int)stack->stack_a[i];
		if ((int)(stack->stack_a[i]) < *min)
			*min = (int)stack->stack_a[i];
		i++;
	}
}

void	ft_arcodage3(t_push_swap *stack)
{
	int	min;
	int	max;

	if (ft_verif_sort(stack) == 0)
		return ;
	if (stack->nb == 2)
		ft_quick_sort_2(stack);
	find_min_max(stack, &min, &max);
	ft_arcodage2(stack, min, max);
	return ;
}

void	ft_check_and_push(t_push_swap *stack, int min, int max)
{
	if ((int)(*stack->stack_a) == min || (int)(*stack->stack_a) == max)
		ft_pb(stack);
	else
		ft_ra(stack);
}

void	ft_check_and_rotate(t_push_swap *stack)
{
	if ((int)*stack->stack_a > (int)*(stack->stack_a + 1)
		|| (int)*stack->stack_b > (int)*stack->stack_a)
	{
		ft_pa(stack);
		ft_ra(stack);
	}
}
