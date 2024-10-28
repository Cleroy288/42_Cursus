/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <chleroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:55:36 by chleroy           #+#    #+#             */
/*   Updated: 2023/07/27 13:07:54 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_free_join_and_destroy_all(t_general *general)
{
	int		i;

	if (general->th)
	{
		i = -1;
		while (++i < general->nb_of_philo)
			pthread_join(general->th[i], NULL);
	}
	if (general->mutex)
	{
		i = -1;
		pthread_mutex_destroy(&general->mutex_general);
		pthread_mutex_destroy(&general->mutex_msg);
		while (++i < general->nb_of_philo)
			pthread_mutex_destroy(&general->mutex[i]);
	}
	if (general->mutex)
		free(general->mutex);
	if (general->philo)
		free(general->philo);
	if (general->th)
		free(general->th);
	return (1);
}

void	ft_check_if_still_alive(t_general *general)
{
	int	i;
	int	last_meal;

	i = 0;
	while (i < general->nb_of_philo)
	{
		pthread_mutex_lock(&general->mutex_general);
		last_meal = general->philo[i].last_meal;
		pthread_mutex_unlock(&general->mutex_general);
		if ((ft_get_current_time() - last_meal) >= general->time_to_die)
		{
			ft_put_message(&general->philo[i], "died");
			pthread_mutex_lock(&general->mutex_general);
			general->is_still_alive = 0;
			pthread_mutex_unlock(&general->mutex_general);
			break ;
		}
		i++;
	}
	return ;
}

void	ft_check_all_meals(t_general *general)
{
	int	i;
	int	meal_count;
	int	nb_of_meals_to_eat;

	nb_of_meals_to_eat = 0;
	i = 0;
	while (i < general->nb_of_philo)
	{
		pthread_mutex_lock(&general->mutex_general);
		meal_count = general->philo[i].meal_counters;
		pthread_mutex_unlock(&general->mutex_general);
		if (meal_count >= general->nb_of_meals_to_eat)
			nb_of_meals_to_eat++;
		i++;
	}
	if (nb_of_meals_to_eat == general->nb_of_philo)
	{
		pthread_mutex_lock(&general->mutex_general);
		general->is_still_alive = 0;
		printf("All philo ate\n");
		pthread_mutex_unlock(&general->mutex_general);
	}
}

void	ft_multi_check(t_general *general)
{
	int	isalive;

	pthread_mutex_lock(&general->mutex_general);
	isalive = general->is_still_alive;
	pthread_mutex_unlock(&general->mutex_general);
	while (isalive)
	{
		ft_check_if_still_alive(general);
		if (general->nb_of_meals_to_eat)
			ft_check_all_meals(general);
		pthread_mutex_lock(&general->mutex_general);
		isalive = general->is_still_alive;
		pthread_mutex_unlock(&general->mutex_general);
	}
}

int	main(int ac, char **av)
{
	t_general	general;

	if (ac < 5 || ac > 6)
		return (ft_error(NB_ARG_ERR, 1));
	if (!ft_init_general(&general, ac, av))
		return (1);
	if (!ft_init_philo_mutex_and_thread(&general, -1, -1))
		return (ft_free_join_and_destroy_all(&general));
	ft_multi_check(&general);
	ft_free_join_and_destroy_all(&general);
}
