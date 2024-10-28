/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:55:45 by chleroy           #+#    #+#             */
/*   Updated: 2023/07/27 14:39:01 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# define NB_ARG_ERR "Wrong number of arguments"
# define ONLY_NB_ERR "Arguments should only contain numbers"
# define VALID_NB_ERR "Arguments should contain valid numbers"
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_philo
{
	int					id;
	int					last_meal;
	int					meal_counters;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_general	*general;
}	t_philo;

typedef struct s_general
{
	int					nb_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_of_meals_to_eat;
	int					start;
	int					is_still_alive;
	pthread_mutex_t		*mutex;
	pthread_mutex_t		mutex_general;
	pthread_mutex_t		mutex_msg;
	pthread_t			*th;
	t_philo				*philo;
}	t_general;

void			ft_multi_check(t_general *general);
int				ft_free_join_and_destroy_all(t_general *general);
void			ft_put_message(t_philo *philo, char *msg);
int				ft_atoi(char *str);
int				ft_error(char *str, int i);
int				ft_isalpha(int c);
void			ft_sleep(int time);
int				ft_init_general(t_general *general, int ac, char **av);
int				ft_init_philo_mutex_and_thread(t_general *general,
					int i, int j);
int				ft_get_current_time(void);
void			*routine(void *obj);

#endif
