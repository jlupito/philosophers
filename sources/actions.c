/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:39:58 by jarthaud          #+#    #+#             */
/*   Updated: 2023/06/26 17:49:42 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_dead(t_data *data)
{
	int	i;

	while (!data->meals_complete)
	{
		i = -1;
		while (++i < data->nb_philo && !data->dead)
		{
			if ((ft_get_time() - data->philos[i].t_last_meal) > data->t_die)
			{
				write_message("died", data->philos[i].id, data);
				pthread_mutex_lock(&data->dead_lock);
				data->dead = 1;
				pthread_mutex_unlock(&data->dead_lock);
			}
			usleep(100);
		}
		if (data->dead)
			break ;
		i = 0;
		while (data->meals_to_eat != -1 && i < data->nb_philo
			&& data->philos[i].meals_eaten >= data->meals_to_eat)
			i++;
		if (i == data->nb_philo)
			data->meals_complete = 1;
	}
}

void	process_eating(t_philo *philos)
{
	pthread_mutex_lock(&philos->data->forks[philos->left_fork]);
	write_message("has taken a fork", philos->id, philos->data);
	pthread_mutex_lock(&philos->data->forks[philos->right_fork]);
	write_message("has taken a fork", philos->id, philos->data);
	// pthread_mutex_lock(&philos->data->dead_lock);
	write_message("is eating", philos->id, philos->data);
	philos->t_last_meal = ft_get_time();
	// pthread_mutex_unlock(&philos->data->dead_lock);
	ft_usleep(philos->data->t_eat, philos->data);
	philos->meals_eaten++;
	pthread_mutex_unlock(&philos->data->forks[philos->left_fork]);
	pthread_mutex_unlock(&philos->data->forks[philos->right_fork]);
}

void	*routine(void *arg)
{
	t_philo		*philos;

	philos = (t_philo *) arg;
	if (philos->id % 2)
		usleep(100);
	while (!philos->data->dead)
	{
		if (philos->data->meals_complete)
			break ;
		process_eating(philos);
		write_message("is sleeping", philos->id, philos->data);
		ft_usleep(philos->data->t_sleep, philos->data);
		write_message("is thinking", philos->id, philos->data);
	}
	return (NULL);
}

int	process_philo(t_data *data)
{
	int	i;

	i = -1;
	data->t_start = ft_get_time();
	while (++i < data->nb_philo)
	{
		pthread_create(&data->philos[i].t1, NULL, &routine, &data->philos[i]);
		data->philos[i].t_last_meal = ft_get_time();
	}
	check_dead(data);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->philos[i].t1, NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	return (0);
}
