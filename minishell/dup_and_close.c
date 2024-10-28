/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:28:16 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 16:33:48 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup2(int fd, int std)
{
	if (dup2(fd, std) == -1)
		perror("dup2");
}

void	ft_close(int *fd)
{
	if (*fd == -1)
		return ;
	if (close(*fd) == -1)
		perror("close");
}
