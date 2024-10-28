/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arg_for_echo_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:43:52 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:44:42 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_t_quotes(t_sub_var *quotes)
{
	(*quotes).i = 0;
	(*quotes).j = 0;
	(*quotes).in_double_quotes = 0;
	(*quotes).in_single_quotes = 0;
	(*quotes).new_str = NULL;
	(*quotes).start = 0;
}
