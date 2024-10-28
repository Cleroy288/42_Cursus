/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:25:41 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/11 14:33:20 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(char const *str, ...);
size_t	ft_strlen(char *s);
size_t	ft_len_nb(long long int nb);
size_t	ft_putnbr(int nb);
size_t	ft_putstr(char *s);
size_t	ft_int_len(long long nb, int base);
int		ft_printf(char const *str, ...);
size_t	ft_putchar(int c);
size_t	ft_dispatch(va_list ag, char c);
int		ft_is_in(char c, char *pos);
size_t	ft_putnbr_base(long long int nbr, char *base, size_t base_len);
size_t	ft_putmem(unsigned long int ptr, char *base);
size_t	ft_putnbr_u(unsigned int nb);
void	ft_printhex(unsigned int nb, char *base, size_t *len);
size_t	ft_putnbr_hex(unsigned long int nbr, char *base, size_t base_len);
size_t	ft_ret_ptb(unsigned long long int nb, size_t base_len);

#endif 
