/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_args_in_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:39:32 by chleroy           #+#    #+#             */
/*   Updated: 2023/06/05 11:39:47 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_set_args_in_struct(char **argv, int argc, t_pipex *st)
{
	int		i;
	int		j;

	i = 2;
	j = 0;
	st->cmd_args_count = argc - 3;
	st->cmd_args = malloc(sizeof(char **) * (argc - 3 + 1));
	if (!st->cmd_args)
	{
		ft_putstr_fd("error malloc\n", 1);
		exit(EXIT_FAILURE);
	}
	while (i != argc - 1)
	{
		st->cmd_args[j] = ft_split(argv[i], ' ');
		if (!st->cmd_args[j])
		{
			ft_putstr_fd("error split\n", 1);
			ft_free_what_u_give_me(st, 1, 0);
			exit(EXIT_FAILURE);
		}
		j++;
		i++;
	}
	st->cmd_args[j] = NULL;
}
