/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_rb_rra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:32:06 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/19 10:32:10 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_ra(t_push_swap *t_push_swap)
{
	long	i;
	long	tmp;

	i = 0;
	if (!t_push_swap->stack_a || !t_push_swap->stack_b)
		return ;
	if (t_push_swap->len_stack_a > 1)
	{
		tmp = t_push_swap->stack_a[0];
		while (i != t_push_swap->len_stack_a - 1)
		{
			t_push_swap->stack_a[i] = t_push_swap->stack_a[i + 1];
			i++;
		}
		t_push_swap->stack_a[t_push_swap->len_stack_a - 1] = tmp;
		ft_putstr_fd("ra\n", 1);
	}
}

void	ft_rb(t_push_swap *t_push_swap)
{
	long	i;
	long	tmp;

	i = 0;
	if (!t_push_swap->stack_a || !t_push_swap->stack_b)
		return ;
	if (t_push_swap->len_stack_b > 1)
	{
		tmp = t_push_swap->stack_b[0];
		while (i != t_push_swap->len_stack_b - 1)
		{
			t_push_swap->stack_b[i] = t_push_swap->stack_b[i + 1];
			i++;
		}
		t_push_swap->stack_b[t_push_swap->len_stack_b - 1] = tmp;
	}
	ft_putstr_fd("rb\n", 1);
}

void	ft_rra(t_push_swap *t_push_swap)
{
	long	i;
	long	tmp_last;

	if (!t_push_swap->stack_a || t_push_swap->len_stack_a < 2)
		return ;
	tmp_last = t_push_swap->stack_a[t_push_swap->len_stack_a - 1];
	i = t_push_swap->len_stack_a - 1;
	while (i > 0)
	{
		t_push_swap->stack_a[i] = t_push_swap->stack_a[i - 1];
		i--;
	}
	t_push_swap->stack_a[0] = tmp_last;
	ft_putstr_fd("rra\n", 1);
}
