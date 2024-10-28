/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:42:52 by chleroy           #+#    #+#             */
/*   Updated: 2023/06/07 10:58:52 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	st;

	if (argc < 3)
		exit(EXIT_FAILURE);
	st.env = env;
	st.infile_fd = open(argv[1], O_RDONLY);
	if (st.infile_fd == -1)
	{
		ft_putstr_fd("error open infile\n", 1);
		exit(EXIT_FAILURE);
	}
	st.outfile_path = argv[argc - 1];
	st.outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (st.outfile_fd == -1)
	{
		ft_putstr_fd("error open outfile\n", 1);
		exit(EXIT_FAILURE);
	}
	ft_set_args_in_struct(argv, argc, &st);
	ft_init_and_execute_process(&st);
	ft_free_what_u_give_me(&st, 1, 1);
}
