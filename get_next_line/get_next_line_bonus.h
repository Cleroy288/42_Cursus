/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:31:27 by chleroy           #+#    #+#             */
/*   Updated: 2023/04/25 12:31:29 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2, int *is_new_line);
size_t	ft_strlen(char *str);
char	*ft_free_an_ret_null(char *str, char **str2, char *buffer);
size_t	ft_find_nl(char *str);
char	*ft_get_line(char *ret, int fd, int is_new, size_t len_read_from_file);

#endif
