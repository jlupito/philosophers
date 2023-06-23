/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:39:58 by jarthaud          #+#    #+#             */
/*   Updated: 2023/06/23 17:03:37 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


void	check_dead(t_data *data)
{
	int	i;

	while (!data->stop)
	{
		i = -1;
		while (++i < data->nb_philo && !data->dead)
		{
			pthread_mutex_lock(&data->dead_lock);
			if ((ft_get_time() - data->philos[i].time_last_eaten) > data->time_die)
			{
				write_message("died", data->philos[i].id, data);
				data->dead = 1;
			}
			pthread_mutex_unlock(&data->dead_lock);
			usleep(100);
		}
		if (data->dead)
			break ;
		i = 0;
		if (data->meals_to_eat != -1 && i < data->nb_philo && data->philos[i].meals_eaten >= data->meals_to_eat)
			i++;
		if (i == data->nb_philo)
			data->stop = 1;
	}
}

void	process_eating(t_philo *philos)
{
	pthread_mutex_lock(&philos->data->forks[philos->left_fork]);
	write_message("has taken a fork", philos->id, philos->data);
	pthread_mutex_lock(&philos->data->forks[philos->right_fork]);
	write_message("has taken a fork", philos->id, philos->data);
	write_message("is eating", philos->id, philos->data);
	// philos->time_last_eaten = ft_get_time();
	ft_usleep(philos->data->time_eat, philos->data);
	philos->meals_eaten++;
	pthread_mutex_unlock(&philos->data->forks[philos->left_fork]);
	pthread_mutex_unlock(&philos->data->forks[philos->right_fork]);
}

void	*routine(void *arg)
{
	t_philo		*philos;

	philos = (t_philo *)arg;
	if (philos->id % 2)
		usleep(15000);
	while (!philos->data->dead)
	{
		process_eating(philos);
		// philos->time_last_eaten = ft_get_time();
		if (philos->meals_eaten == philos->data->meals_to_eat)
			break ;
		write_message("is sleeping", philos->id, philos->data);
		ft_usleep(philos->data->time_sleep, philos->data);
		write_message("is thinking", philos->id, philos->data);
	}
	return (NULL);
}

int	process_philo(t_data *data)
{
	int	i;

	i = -1;
	data->time_start = ft_get_time();
	while (++i < data->nb_philo)
	{
		pthread_create(&data->philos[i].t1, NULL, &routine, &data->philos[i]);
		data->philos[i].time_last_eaten = ft_get_time();
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
