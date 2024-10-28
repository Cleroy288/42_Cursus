/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:44:20 by chleroy           #+#    #+#             */
/*   Updated: 2023/06/07 10:58:59 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./lib/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_pipex
{
	char		*input_file;
	char		*output_file;
	int			cmd_args_count;
	char		***cmd_args;
	int			pipefds[100][2];
	int			current_pipe[2];
	pid_t		*pids;
	int			infile_fd;
	int			outfile_fd;
	char		*outfile_path;
	char		**env;
	char		*path;
	char		**path_splitted;

}				t_pipex;

void	ft_set_args_in_struct(char **argv, int argc, t_pipex *st);
void	ft_free_what_u_give_me(t_pipex *st, int one_for_cmmargs, int one_pids);
char	*ft_get_path(t_pipex *st, int command_nb);
void	ft_close_children(t_pipex *st, int pos);
void	ft_close_parent(int pos, t_pipex *st);
void	ft_close(int *fd, t_pipex *st);
void	ft_dup2(int fd, int std, t_pipex *st);
void	ft_child_process(t_pipex *st, int i);
void	ft_init_and_execute_process(t_pipex *st);
void	ft_close(int *fd, t_pipex *st);
void	ft_dup2(int fd, int std, t_pipex *st);

#endif
