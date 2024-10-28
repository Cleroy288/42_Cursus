/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chleroy <charles.leroy288@gmail.co>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:55:56 by chleroy           #+#    #+#             */
/*   Updated: 2023/07/27 12:55:58 by chleroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_put_message(t_philo *philo, char *msg)
{
	int	time;
	int	is_still_alive;

	time = ft_get_current_time() - philo->general->start;
	pthread_mutex_lock(&philo->general->mutex_msg);
	pthread_mutex_lock(&philo->general->mutex_general);
	is_still_alive = philo->general->is_still_alive;
	pthread_mutex_unlock(&philo->general->mutex_general);
	if (is_still_alive)
		printf("%d %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->general->mutex_msg);
}

int	ft_main_course(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_put_message(philo, FORK);
	if (philo->general->nb_of_philo == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	ft_put_message(philo, FORK);
	ft_put_message(philo, EAT);
	pthread_mutex_lock(&philo->general->mutex_general);
	philo->last_meal = ft_get_current_time();
	pthread_mutex_unlock(&philo->general->mutex_general);
	ft_sleep(philo->general->time_to_eat);
	pthread_mutex_lock(&philo->general->mutex_general);
	philo->meal_counters += 1;
	pthread_mutex_unlock(&philo->general->mutex_general);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_put_message(philo, SLEEP);
	ft_sleep(philo->general->time_to_sleep);
	ft_put_message(philo, THINK);
	return (0);
}

void	*routine(void	*arg)
{
	t_philo	*philo;
	int		isalive;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->general->mutex_general);
	isalive = philo->general->is_still_alive;
	pthread_mutex_unlock(&philo->general->mutex_general);
	while (isalive)
	{
		if (ft_main_course(philo))
			break ;
		pthread_mutex_lock(&philo->general->mutex_general);
		isalive = philo->general->is_still_alive;
		pthread_mutex_unlock(&philo->general->mutex_general);
	}
	return (NULL);
}
