/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:55:27 by chleroy           #+#    #+#             */
/*   Updated: 2023/07/30 15:21:47 by charleslero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_general(t_general *general, int ac, char **av)
{
	general->is_still_alive = 1;
	general->nb_of_philo = ft_atoi(av[1]);
	general->time_to_die = ft_atoi(av[2]);
	general->time_to_eat = ft_atoi(av[3]);
	general->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		general->nb_of_meals_to_eat = ft_atoi(av[5]);
	if (general->nb_of_philo < 1 || general->time_to_die < 1
		|| general->time_to_eat < 1 || general->time_to_sleep < 1
		|| (general->nb_of_meals_to_eat < 1 && av[5] && ac == 6)
		|| general->nb_of_philo > 250)
		return (ft_error(VALID_NB_ERR, 0));
	general->philo = malloc(sizeof(t_philo) * general->nb_of_philo);
	if (!general->philo)
		return (ft_error("Malloc Error", 0));
	general->mutex = malloc(sizeof(pthread_mutex_t) * general->nb_of_philo);
	if (!general->mutex)
		return (ft_error("Malloc Error", 0));
	general->th = malloc(sizeof(pthread_t) * general->nb_of_philo);
	if (!general->th)
		return (ft_error("Malloc error", 0));
	return (1);
}

int	ft_init_philo_mutex_and_thread(t_general *general, int i, int j)
{
	while (++i < general->nb_of_philo)
	{
		general->philo[i].id = i + 1;
		general->philo[i].left_fork = &general->mutex[i];
		general->philo[i].right_fork = &general->mutex[(i + 1)
			% general->nb_of_philo];
		general->philo[i].general = general;
	}
	i = -1;
	while (++i < general->nb_of_philo)
		if (pthread_mutex_init(&general->mutex[i], NULL))
			return (ft_error("Error while creating mutex", 0));
	if (pthread_mutex_init(&general->mutex_general, NULL))
		return (ft_error("Error while creating mutex", 0));
	if (pthread_mutex_init(&general->mutex_msg, NULL))
		return (ft_error("Error while creating mutex", 0));
	general->start = ft_get_current_time();
	while (++j < general->nb_of_philo)
	{
		general->philo[j].last_meal = ft_get_current_time();
		if (pthread_create(&general->th[j], NULL, &routine, &general->philo[j]))
			return (ft_error("Error creating thread", 0));
		ft_sleep(1);
	}
	return (1);
}
