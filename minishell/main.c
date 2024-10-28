/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:14:46 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/19 17:07:15 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexeur	g_data;

void	ft_principal_loop(void)
{
	char	*ret;

	g_data.status = 0;
	ft_first_singal_handler();
	g_data.index_in_mem_stack = 0;
	while (1)
	{
		ft_sec_signal_handler();
		ret = readline("\033[1;33mQuoicouShell> \033[1;32m");
		if (!ret)
			break ;
		ft_signal_handler_default();
		add_history(ret);
		if (ft_process_the_input_validity_quotes(ret))
			continue ;
		ft_verif_exit(ret);
		ret = ft_set_variables_in_place(ret);
		ft_process_and_dispatch(ret);
		free(ret);
		ft_free_in_main_process();
	}
	clear_history();
}

void	allocate_env_memory(char **env, int len)
{
	if (!env)
	{
		g_data.env = malloc(1);
		if (!g_data.env)
			exit(EXIT_FAILURE);
		g_data.env[0] = NULL;
	}
	else
	{
		g_data.env = malloc(sizeof(char *) * (len + 1));
		if (!g_data.env)
			exit(EXIT_FAILURE);
	}
}

void	copy_env_content(char **env, int len)
{
	int		j;

	j = 0;
	while (j < len)
	{
		g_data.env[j] = ft_strdup(env[j]);
		if (!g_data.env[j])
		{
			ft_free_double_pointer(g_data.env);
			exit(0);
		}
		j++;
	}
	g_data.env[j] = NULL;
	g_data.size_env_tab = len;
}

void	ft_copy_env(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
			i++;
	}
	allocate_env_memory(env, i);
	if (env)
		copy_env_content(env, i);
}

int	main(int argc, char **argv, char **env)
{
	printf("░██████╗░██╗░░░██╗░█████╗░██╗░█████╗░░█████╗░██");
	printf("╗░░░██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\n");
	printf("██╔═══██╗██║░░░██║██╔══██╗██║██╔══██╗██╔══██╗██");
	printf("║░░░██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░\n");
	printf("██║██╗██║██║░░░██║██║░░██║██║██║░░╚═╝██║░░██║██");
	printf("║░░░██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░\n");
	printf("╚██████╔╝██║░░░██║██║░░██║██║██║░░██╗██║░░██║██");
	printf("║░░░██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░\n");
	printf("░╚═██╔═╝░╚██████╔╝╚█████╔╝██║╚█████╔╝╚█████╔╝╚█");
	printf("█████╔╝██████╔╝██║░░██║███████╗███████╗███████╗\n");
	printf("░░░╚═╝░░░░╚═════╝░░╚════╝░╚═╝░╚════╝░░╚════╝░░╚");
	printf("═════╝░╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝\n");
	ft_init_struct();
	ft_copy_env(env);
	g_data.commands[0] = NULL;
	g_data.return_value = 0;
	if (argc > 2 && argv[1] != NULL)
		return (printf("just execute minishell without arguments\n"));
	ft_principal_loop();
	ft_free_memory_stack();
	return (0);
}
