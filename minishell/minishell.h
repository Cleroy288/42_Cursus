/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:22:41 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/20 12:54:24 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/libft.h"

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <limits.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_node
{
	int				value;
	char			*command;
	char			**splitted_command;
	struct s_node	*next;
	struct s_node	*prev;
}		t_node;

typedef struct s_sub_var
{
	char	*arg;
	char	*value;
	char	*new_str;
	char	*s;
	int		i;
	int		j;
	int		in_single_quotes;
	int		in_double_quotes;
	int		start;
}		t_sub_var;

typedef struct s_utils_main
{
	int		i;
	int		len;
	int		count;
	char	quote;
}		t_utils_main;

typedef struct s_list_shell
{
	char	*command;
	t_node	*head;
	t_node	*tail;
}		t_list_shell;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_lexeur
{
	void			*stack_withe_mem_address[1000];
	char			*initial_command;
	char			*return_str_from_rdl;
	char			**commands[1000];
	char			**command_in_pipes;
	char			*treated_command;
	char			*input_file;
	char			*output_file;
	char			*here_doc;
	char			*word_here_doc;
	char			*path;
	char			**path_splitted;
	char			**env;
	int				infile_fd;
	int				outfile_fd;
	int				append_is_one;
	int				commands_count;
	int				signal_here_doc;
	int				size_env_tab;
	int				pipefds[1000][2];
	int				invalid_is_one;
	int				index_in_mem_stack;
	int				return_value;
	int				status;
	pid_t			pids[1000];
	t_list_shell	*list;
	t_node			*node;
	t_env			*lst_env;
	t_sub_var		*sub_var;
	t_utils_main	*utils_main;
}				t_lexeur;

typedef struct s_quotes
{
	int		i;
	int		j;
	char	c;
}				t_quotes;

extern t_lexeur	g_data;

t_env		*ft_lstlast_env(t_env *lst);
t_env		*ft_lstnew_env(char *content, char *str);
t_env		*ft_tab_to_lst(char **tab);
void		ft_free_double_pointer(char **ptr);
void		ft_dup2(int fd, int std);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
void		ft_lstclear_env(t_env *lst);
void		ft_signal_handler_default(void);
void		ft_signal_handler_child(void);
void		ft_principal_loop(void);
void		ft_verif_exit(char *ret);
void		ft_principal_pipex_function(void);
void		ft_set_spaces_in_command(void);
void		ft_parent(int pos);
void		ft_child_process(int i);
void		ft_child(int pos);
void		ft_pipe(int pos);
void		ft_fork(int pos);
void		skip_until_letter(int *i, int *occurrences, char *str, char letter);
void		reset_prompt(int sig);
void		ft_free_env(void);
void		reset_signals(void);
void		handle_dup_close(void);
void		exec_command(int i);
void		handle_child_process(int i);
void		ft_one_command_only(void);
void		ft_initialize_pipes(void);
void		ft_handle_child_process(int i);
void		ft_free_command(int nb);
void		ft_execute_processes(void);
void		ft_wait_for_processes(void);
void		ft_set_ret_in_command_and_options(void);
void		ft_extract_commands_and_options(void);
void		ft_create_command_with_no_in_out_file_or_redirections(void);
void		ft_process_and_dispatch(char *ret);
void		ft_first_singal_handler(void);
void		ft_sec_signal_handler(void);
void		ft_free_in_main_process(void);
void		ft_init_outputfile(void);
void		ft_init_inputfile(void);
void		ft_init_here_doc_word(void);
void		ft_init_initial_command(void);
void		ft_init_return_from_rdl(void);
void		ft_init_command_splitted_in_pipes(void);
void		list_add_shell(t_list_shell *list, int value);
void		list_free_shell(t_list_shell *list);
void		ft_lstadd_back_shell(t_list_shell *lst, t_node *new);
void		ft_set_value(char *key, char *value, t_env **lst);
void		ft_free_outputfile(void);
void		ft_free_inputfile(void);
void		ft_free_here_doc_word(void);
void		ft_free_initial_command(void);
void		ft_free_return_from_rdl(void);
void		ft_free_path_splitted(void);
void		ft_free_path(void);
void		ft_free_one_tab_in_commands(int index);
void		ft_free_commands(void);
void		ft_free_treated_command(void);
void		ft_echo(int nb);
void		ft_env(void);
void		ft_unset(t_env	**lst, char *str);
void		ft_close(int *fd);
void		ft_update_old_pwd(char *env_info);
void		ft_init_and_execute_process(void);
void		ft_free_memory_stack(void);
void		ft_is_command_cd(void);
void		ft_export_add(t_env **lst, char *str, char *content);
void		ft_update_pwd(char *new_path);
void		ft_signal_handler_here_doc(void);
void		ft_find_right_env_line(void);
void		ft_signal_handler_parent(void);
void		ft_here_doc_fulfilling(void);
void		ft_set_args_in_struct(void);
void		ft_extract_input_output_file(char *s);
char		*ft_join_and_set_char(char *s1, char *s2, char c);
void		skip_special_word(char *s, size_t *i, int *nb);
void		skip_normal_word(char *s, size_t *i, char *sp, int *nb);
void		append_value_or_var(char *new_str, int *j, char *value, int start);
void		ft_init_t_quotes(t_sub_var *quotes);
void		ft_display(int *tab, int i[4]);
void		ft_export_basique(void);
void		ft_add_info(int len, t_env *temp, char *str, char *tmp);
void		ft_export_modify(t_env **lst, char *str, int nb_of_command);
void		ft_increment(int *end, int *ret, char **str, int incr);
void		ft_right_command_quotes(char *quotes, int *i, char *str);
char		*ft_get_path(int command_nb, int i);
char		*ft_remove_quotes(const char *str);
char		*ft_str_without_w(char *str, char *take_out);
char		*ft_find_line(char *str);
char		*ft_str_without_w_free_str(char *str, char *take_out);
char		*ft_make_str_without_one_letter_free_str(char *str, char letter);
char		*ft_magic(char *str);
char		*go_get_right_command(char *str, int nb_command);
char		*ft_set_variables_in_place(char *s);
char		*ft_set_variables_in_here_doc(char *line_to_here_doc);
char		*ft_last_pass(char *s, int *index_i, int *index_j);
char		**split_in_valid_pipes(char *s);
char		**ft_takout_qoutes_in_command_wh_is_not_echo(char **s);
char		*ft_strldup(char *s, int len);
char		*find_next_word(char *s, int *i, char *c);
char		**split_in_valid_spaces(char *s);
char		*ft_return_value(int end, int start, char *s);
char		*ft_make_word(char *s, size_t *index, char *sp);
char		**ft_special_split(char *s, char *sp);
char		*ft_find_argument_in_env_value(char *arg);
char		*get_env_var_name(char *s, int *i);
char		*extract_everything_after_char(char *s, char c);
char		*ft_remove(char *tmp, int nb_of_command);
char		*ft_make_str_without_one_letter(char *str, char c);
char		ft_check_for_sec_arg(char *str);
char		*ft_treat_command_for_echo(char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_find_in_env(char *s);
char		*ft_skip_and_cpy(char *str, char *word, int *nb);
char		*ft_set_variable_in_str(char *s1, char *word, char *s2);
char		*ft_last_operation_remove_single_quotes(char *s);
char		*ft_is_dollars_sec_part(char **val, char **var, char *ret, char *s);
char		*ft_is_dollars(char *s, int *i, char *ret);
char		*ft_set_print_variabels(char *s);
char		*ft_takeout_part_2(char *s, int *k, char *ret, int i);
char		*ft_takeout_single_quotes(char *s);
char		*ft_extra_arg_in_single(char *s);
char		*ft_go_get_right_command_part_2(int *i, char *str, char *quotes);
int			ft_go_to_quotes(char *s);
int			ft_quotes(char *s, int i, int *j);
int			ft_skip_n(char *new, int is_n, int *count, int fin);
int			ft_modify_shlvl(int modif);
int			handle_errors(int i);
int			ft_fulfilling(int fd_here_doc);
int			check_pipe_count(char *s);
int			check_quotes_validity(char *s, char pos_1, char pos_2);
int			check_escape_validity(char *s);
int			check_consecutive_pipes(char *s);
int			ft_process_the_input_validity_quotes(char *s);
int			ft_go_at_next_quotes(char *s, int index, char *c);
int			ft_nb_of_command(char *s);
int			ft_skipping(char *s, int j_index, char *c);
int			update_j_index(char *s, int *j_index, char *c);
int			ft_is_char_in_str(char *s, char c, char c2);
int			count_valid_spaces(char *s, char *c, int *i);
int			nb_of_word_for_valid_spaces(char *s);
int			handle_quotes(char *s, char *c, int *j);
int			ft_len(char *s);
int			ft_cd_option(int i, char **path);
int			ft_is_on_char(char c, char *s);
int			ft_nb_of_words(char *s, char *sp);
int			ft_print_path(char *s);
int			full(char *value, char *new_str, int j);
int			ft_find_len_env_value(char *s);
int			ft_len_word(char *s, int index);
int			ft_len_new_str(char *s);
int			ft_iswhitespace(char c);
int			ft_is_n(char **str);
int			calculate_result_length(char *string, char *word);
int			ft_lstsize_env(t_env *lst);
int			ft_builtin(int i);
int			ft_search_for_character(char *s, char c);
int			ft_len_env_tab(void);
int			ft_free_function(void);
int			ft_init_struct(void);
int			check_and_skip(char *str, char *take_out, int i);
void		ft_count(int *count);

#endif