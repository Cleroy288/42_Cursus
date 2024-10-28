/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:00:40 by chleroy           #+#    #+#             */
/*   Updated: 2023/06/05 11:47:49 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	ssize_t	ret;

	if (fd >= 0)
	{
		ret = write (fd, &c, 1);
		if (ret == -1)
		{
			return ;
		}
	}
	else
		return ;
}
