/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_radix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:10:51 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/19 10:11:16 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_arcodage_conditions(t_push_swap *stack)
{
	if ((int)stack->stack_a[0] < (int)stack->stack_a[1]
		&& (int)stack->stack_a[1] > (int)stack->stack_a[2]
		&& (int)stack->stack_a[0] > (int)stack->stack_a[2])
		ft_rra(stack);
	else if ((int)stack->stack_a[0] < (int)stack->stack_a[1]
		&& (int)stack->stack_a[1] > (int)stack->stack_a[2]
		&& (int)stack->stack_a[0] < (int)stack->stack_a[2])
	{
		ft_sa(stack);
		ft_ra(stack);
	}
	else if ((int)stack->stack_a[0] > (int)stack->stack_a[1]
		&& (int)stack->stack_a[1] < (int)stack->stack_a[2]
		&& (int)stack->stack_a[0] > (int)stack->stack_a[2])
		ft_ra(stack);
	else if ((int)stack->stack_a[0] > (int)stack->stack_a[1]
		&& (int)stack->stack_a[1] < (int)stack->stack_a[2]
		&& (int)stack->stack_a[0] < (int)stack->stack_a[2])
		ft_sa(stack);
}

void	ft_arcodage(t_push_swap *stack)
{
	if ((int)stack->stack_a[0] > (int)stack->stack_a[1]
		&& (int)stack->stack_a[1] > (int)stack->stack_a[2])
	{
		ft_ra(stack);
		ft_sa(stack);
	}
	else
		ft_arcodage_conditions(stack);
}

void	ft_arcodage2(t_push_swap *stack, int min, int max)
{
	while (stack->len_stack_a > 3)
		ft_check_and_push(stack, min, max);
	if ((int)*stack->stack_b > (int)*(stack->stack_b + 1))
		ft_sb(stack);
	if (ft_verif_sort(stack) == 1)
		ft_arcodage(stack);
	ft_pa(stack);
	ft_check_and_rotate(stack);
}

void	ft_put_long_indic(t_push_swap *stack)
{
	int	i;
	int	j;
	int	min_i;
	int	min;

	min_i = 0;
	i = 1;
	while (i < stack->len_stack_a + 1)
	{
		min = INT32_MAX;
		j = 0;
		while (j < stack->len_stack_a)
		{
			if ((int)stack->stack_a[j] < min
				&& (int)(stack->stack_a[j] >> 32) == 0)
			{
				min = (int)stack->stack_a[j];
				min_i = j;
			}
			++j;
		}
		stack->stack_a[min_i] |= (long)i << 32;
		++i;
	}
}

void	ft_radix(t_push_swap *ptr)
{
	int	i;
	int	j;

	j = 0;
	if (ptr->len_stack_a <= 5)
		ft_arcodage3(ptr);
	ft_put_long_indic(ptr);
	while (ft_verif_sort(ptr) == 1)
	{
		i = ptr->len_stack_a;
		while (i--)
		{
			if ((((int)(*ptr->stack_a >> (j + 32))) & 1) == 0)
				ft_pb(ptr);
			else
				ft_ra(ptr);
		}
		j++;
		while (ptr->len_stack_b)
			ft_pa(ptr);
	}
}
