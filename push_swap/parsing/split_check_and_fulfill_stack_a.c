/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_check_and_fulfill_stack_a.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:19:50 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/22 11:26:48 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	ft_check_if_valid(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while ((str[i][j] >= '0' && str[i][j] <= '9') || str[i][j] == '-')
			j++;
		if (str[i][j++] != '\0')
			ft_free_and_exit(str, 0, 0, 0);
		i++;
	}
	return (1);
}

static void	ft_check_if_valid_numbers(char **str)
{
	long	nb;
	int		i;

	i = 0;
	while (str[i])
	{
		nb = 0;
		nb = ft_atoi(str[i]);
		if (nb > INT_MAX || nb < INT_MIN)
			ft_free_and_exit(str, 0, 0, 0);
		i++;
	}
}

static void	ft_check_for_dubbels(t_push_swap *st)
{
	int	i;
	int	j;

	i = 0;
	while (st->ret[i])
	{
		j = i + 1;
		while (st->ret[j])
		{
			if (ft_atoi(st->ret[i]) == ft_atoi(st->ret[j]))
				ft_free_and_exit(0, 0, 0, st);
			j++;
		}
		i++;
	}
}

void	ft_fulfill_stack_a(char **str, t_push_swap *stack)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	stack->stack_a = malloc(sizeof(long) * (stack->len_stack_a + 1));
	if (!stack->stack_a)
		ft_free_and_exit(str, 0, 0, 0);
	stack->stack_b = malloc(sizeof(long) * (stack->len_stack_a + 1));
	if (!stack->stack_b)
		ft_free_and_exit(str, 0, 0, 0);
	i = 0;
	while (str[i])
	{
		stack->stack_a[i] = ft_atoi(str[i]);
		free(str[i]);
		i++;
	}
	free(stack->ret);
}

void	ft_split_check_fulfil_tab(char *str, t_push_swap *stack)
{
	stack->ret = ft_split(str, ' ');
	if (!stack->ret)
		ft_free_and_exit(0, str, 0, stack);
	free(str);
	ft_check_if_valid(stack->ret);
	ft_check_if_valid_numbers(stack->ret);
	ft_check_for_dubbels(stack);
	ft_fulfill_stack_a(stack->ret, stack);
}
