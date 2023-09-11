/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:39:58 by jarthaud          #+#    #+#             */
/*   Updated: 2023/09/07 15:44:07 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	takes_fork(t_philo *philos)
{
	if (!(philos->id % 2))
	{
		pthread_mutex_lock(&philos->data->forks[philos->left_fork]);
		write_message("has taken a fork", philos);
		pthread_mutex_lock(&philos->data->forks[philos->right_fork]);
		write_message("has taken a fork", philos);
	}
	else if (philos->id % 2)
	{
		pthread_mutex_lock(&philos->data->forks[philos->right_fork]);
		write_message("has taken a fork", philos);
		pthread_mutex_lock(&philos->data->forks[philos->left_fork]);
		write_message("has taken a fork", philos);
	}
}

void	gives_fork(t_philo *philos)
{
	if (!(philos->id % 2))
	{
		pthread_mutex_unlock(&philos->data->forks[philos->right_fork]);
		pthread_mutex_unlock(&philos->data->forks[philos->left_fork]);
	}
	else if (philos->id % 2)
	{
		pthread_mutex_unlock(&philos->data->forks[philos->left_fork]);
		pthread_mutex_unlock(&philos->data->forks[philos->right_fork]);
	}
}

void	process_eating(t_philo *philos)
{
	takes_fork(philos);
	write_message("is eating", philos);
	pthread_mutex_lock(&philos->data->dead_lock);
	philos->t_last_meal = ft_get_time();
	pthread_mutex_lock(&philos->data->eat_lock);
	philos->nb_eaten++;
	pthread_mutex_unlock(&philos->data->eat_lock);
	pthread_mutex_unlock(&philos->data->dead_lock);
	ft_usleep(philos->t_eat, philos->data);
	gives_fork(philos);
}
