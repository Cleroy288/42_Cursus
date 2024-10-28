/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2_and_close.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:34:52 by chleroy           #+#    #+#             */
/*   Updated: 2023/06/05 11:34:58 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_dup2(int fd, int std, t_pipex *st)
{
	(void)st;
	if (dup2(fd, std) == -1)
	{
		ft_putstr_fd("error in dup2\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	ft_close(int *fd, t_pipex *st)
{
	(void)st;
	if (*fd == -1)
		return ;
	if (close(*fd) == -1)
	{
		ft_putstr_fd("error close\n", 2);
		exit(EXIT_FAILURE);
	}
}
