/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:15:18 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/05 15:51:33 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	len;

	len = nmemb * size;
	p = malloc(len);
	if (!p)
		return (NULL);
	ft_bzero(p, size * nmemb);
	return (p);
}
