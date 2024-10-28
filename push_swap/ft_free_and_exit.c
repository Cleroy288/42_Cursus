/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_and_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:12:21 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/19 17:42:17 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_free_st(t_push_swap *s)
{
	int	i;

	i = 0;
	if (s && s->ret)
	{
		while (s->ret[i])
		{
			free(s->ret[i]);
			i++;
		}
		free(s->ret);
	}
}

void	ft_free_and_exit(char **argv, char *str, long *stack_a, t_push_swap *s)
{
	int	i;

	i = 0;
	if (s && s->ret)
		ft_free_st(s);
	if (argv)
	{
		while (argv[i])
		{
			free(argv[i]);
			i++;
		}
		free(argv);
	}
	if (str)
		free(str);
	if (stack_a)
		free(stack_a);
	ft_putstr_fd("Error\n", 1);
	exit(EXIT_FAILURE);
}
