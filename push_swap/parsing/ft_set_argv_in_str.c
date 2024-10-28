/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_argv_in_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:16:49 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/19 13:29:18 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	len_str(char **argv)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!argv)
		return (0);
	while (argv[i])
	{
		len += ft_strlen(argv[i]);
		i++;
	}
	len += i + 1;
	return (len);
}

char	*ft_fullfill_str_with_arg(char **argv, int argc, char *str)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	k = 0;
	while (argv[i] && argv && i != argc)
	{
		j = 0;
		if (argv[i][0] == '\0')
			ft_free_and_exit(0, str, 0, 0);
		while (argv[i][j])
		{
			str[k] = argv[i][j];
			j++;
			k++;
		}
		str[k ++] = 32;
		i++;
	}
	str[k] = '\0';
	return (str);
}

char	*ft_set_argv_to_str(char **argv, int argc)
{
	char	*str;

	if (!argv)
		ft_free_and_exit(0, 0, 0, 0);
	str = malloc(sizeof(char) * len_str(argv) + 1);
	if (!str)
		return (0);
	str = ft_fullfill_str_with_arg(argv, argc, str);
	return (str);
}
