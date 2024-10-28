/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fgets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:46:48 by chleroy           #+#    #+#             */
/*   Updated: 2023/06/05 11:47:19 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_fgets(char *str, size_t len_buffer, int fd)
{
	size_t	i;
	char	*s;
	char	c;

	i = 0;
	if (!str || len_buffer == 0 || fd < 0)
		return (NULL);
	s = malloc(sizeof(char) * (len_buffer));
	if (!s)
		return (NULL);
	while (i != len_buffer - 1 && read(fd, &c, 1) == 1)
	{
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return (s);
}
