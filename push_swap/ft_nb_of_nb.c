/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_of_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:13:59 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/19 15:39:33 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_is_ony_nb_and_space(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == 32 || (str[i] >= '0' && str[i] <= '9')
			|| (str[i] == '-' && str[i + 1] >= '0' && str[i + 1] <= '9'))
			i++;
		else
			ft_free_and_exit(0, 0, 0, 0);
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

static int	ft_is_more_than_one_nb(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i + 1])
	{
		if ((str[i] == 32 && (str[i + 1] >= '0' && str[i] <= '9'))
			|| (str[i] == '-' && (str[i + 1] >= '0' && str[i] <= '9')))
			return (1);
		i++;
	}
	return (0);
}

static int	ft_is_only_one_nb(char *str)
{
	size_t		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (((str[i] < '0' || str[i] > '9') && str[i] != '-')
			|| (((str[i] == '-' && str[i + 1] < '0') || str[i + 1] > '9')))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_conditions(char **argv, t_push_swap *stack)
{
	int		ret;

	ret = 0;
	if ((argv[stack->i][stack->j + 1] == 32 && argv[stack->i][stack->j] >= '0'
		&& argv[stack->i][stack->j] <= '9'))
		ret++;
	else if ((argv[stack->i][stack->j + 1] == '\0'
		&& argv[stack->i][stack->j] >= '0' && argv[stack->i][stack->j] <= '9'))
		ret ++;
	else
		ret = -1;
	return (ret);
}

long	ft_nb_of_nb(char **argv, t_push_swap *stack)
{
	stack->i = 1;
	stack->nb2 = 0;
	if (!argv)
		return (-1);
	while (argv[stack->i])
	{
		stack->j = 0;
		if (ft_is_more_than_one_nb(argv[stack->i]) == 1
			&& ft_is_ony_nb_and_space(argv[stack->i]) == 1)
		{
			while (argv[stack->i][stack->j ++])
			{
				if (ft_conditions (argv, stack) != -1)
					stack->nb2++;
			}
		}
		else if (ft_is_only_one_nb(argv[stack->i]) == 1)
			stack->nb2++;
		else
			ft_free_and_exit(0, 0, 0, 0);
		stack->i++;
	}
	return (stack->nb2);
}
