/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa_sb_pb_pa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:35:23 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/19 10:35:27 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_sa(t_push_swap *t_push_swap)
{
	long	tmp;

	if (!t_push_swap->stack_a && t_push_swap->len_stack_a > 2)
		return ;
	if (t_push_swap->stack_a && t_push_swap->len_stack_a >= 2)
	{
		tmp = t_push_swap->stack_a[0];
		t_push_swap->stack_a[0] = t_push_swap->stack_a[1];
		t_push_swap->stack_a[1] = tmp;
		ft_putstr_fd("sa\n", 1);
	}
}

void	ft_sb(t_push_swap *t_push_swap)
{
	long	tmp;

	if (!t_push_swap->stack_b && t_push_swap->len_stack_b > 2)
		return ;
	if (t_push_swap->stack_b && t_push_swap->len_stack_b >= 2)
	{
		tmp = t_push_swap->stack_b[0];
		t_push_swap->stack_b[0] = t_push_swap->stack_b[1];
		t_push_swap->stack_b[1] = tmp;
		ft_putstr_fd("sb\n", 1);
	}
}

void	ft_pb(t_push_swap *t_push_swap)
{
	long	i;
	long	tmp;

	if (t_push_swap->len_stack_a == 0 || !t_push_swap->stack_a
		|| !t_push_swap->stack_b)
		return ;
	tmp = t_push_swap->stack_a[0];
	i = 0;
	while (i < t_push_swap->len_stack_a - 1)
	{
		t_push_swap->stack_a[i] = t_push_swap->stack_a[i + 1];
		i++;
	}
	i = t_push_swap->len_stack_b;
	while (i > 0)
	{
		t_push_swap->stack_b[i] = t_push_swap->stack_b[i - 1];
		i--;
	}
	t_push_swap->stack_b[0] = tmp;
	t_push_swap->stack_a[t_push_swap->len_stack_a - 1] = 0;
	t_push_swap->len_stack_a--;
	t_push_swap->len_stack_b++;
	ft_putstr_fd("pb\n", 1);
}

void	ft_pa(t_push_swap *t_push_swap)
{
	long	i;
	long	tmp;

	if (t_push_swap->len_stack_b == 0 || !t_push_swap->stack_a
		|| !t_push_swap->stack_b)
		return ;
	tmp = t_push_swap->stack_b[0];
	i = 0;
	while (i < t_push_swap->len_stack_b - 1)
	{
		t_push_swap->stack_b[i] = t_push_swap->stack_b[i + 1];
		i++;
	}
	i = t_push_swap->len_stack_a;
	while (i > 0)
	{
		t_push_swap->stack_a[i] = t_push_swap->stack_a[i - 1];
		i--;
	}
	t_push_swap->stack_a[0] = tmp;
	t_push_swap->stack_b[t_push_swap->len_stack_b - 1] = 0;
	t_push_swap->len_stack_a++;
	t_push_swap->len_stack_b--;
	ft_putstr_fd("pa\n", 1);
}
