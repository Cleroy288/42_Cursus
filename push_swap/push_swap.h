/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:25:22 by chleroy           #+#    #+#             */
/*   Updated: 2023/05/22 10:52:23 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./lib/libft.h"
# include <limits.h>
# include <stdint.h>

typedef struct s_push_swap
{
	long	*stack_a;
	long	*stack_b;
	long	len_stack_a;
	long	len_stack_b;
	int		nb;
	size_t	i;
	size_t	j;
	long	nb2;
	long	sign;
	char	**ret;

}	t_push_swap;

void	ft_pb(t_push_swap *t_push_swap);
void	ft_pa(t_push_swap *t_push_swap);
void	ft_sb(t_push_swap *t_push_swap);
void	ft_sa(t_push_swap *t_push_swap);
void	ft_ra(t_push_swap *t_push_swap);
void	ft_rb(t_push_swap *t_push_swap);
void	ft_rra(t_push_swap *t_push_swap);
char	*ft_set_argv_to_str(char **argv, int argc);
void	ft_free_and_exit(char **argv, char *str, long *stack_a, t_push_swap *s);
void	ft_split_check_fulfil_tab(char *str, t_push_swap *stack);
void	ft_radix(t_push_swap *ptr);
void	ft_arcodage3(t_push_swap *stack);
void	ft_arcodage2(t_push_swap *stack, int min, int max);
void	ft_arcodage(t_push_swap *stack);;
int		ft_verif_sort(t_push_swap *t_push_swap);
long	*ft_change_val_tab_to_rank(long *tab, int nb_of_nb, t_push_swap *stack);
void	ft_radix(t_push_swap *stack);
void	ft_put_long_indic(t_push_swap *stack);
void	ft_check_and_push(t_push_swap *stack, int min, int max);
void	ft_check_and_rotate(t_push_swap *stack);
long	ft_nb_of_nb(char **argv, t_push_swap *stack);

#endif
