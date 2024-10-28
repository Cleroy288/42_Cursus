/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:14:30 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/22 12:45:18 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_push_swap	stack;
	char		*str;

	if (argc <= 2)
		return (1);
	stack.len_stack_a = ft_nb_of_nb(argv, &stack);
	stack.len_stack_b = 0;
	str = ft_set_argv_to_str(argv, argc);
	ft_split_check_fulfil_tab(str, &stack);
	ft_change_val_tab_to_rank(stack.stack_a, stack.len_stack_a, &stack);
	ft_radix(&stack);
	free(stack.stack_a);
	free(stack.stack_b);
}
