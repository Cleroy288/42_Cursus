/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:27 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/24 22:45:54 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ftpts_fd(char *s, int fd, int i)
{
	if (!s || fd < 0 || i == 0)
		return ;
	if (s)
		while (s[++i])
			write (fd, &s[i], 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (fd < -1)
		return ;
	ftpts_fd(s, fd, -1);
	write (fd, "\n", 1);
}
