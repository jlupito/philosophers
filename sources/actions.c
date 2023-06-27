/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:39:58 by jarthaud          #+#    #+#             */
/*   Updated: 2023/06/27 17:53:19 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_meals(t_data *data)
{
	int	meals;
	int	i;

	meals = 0;
	i = -1;
	if (data->meals_to_eat == -1)
		return (0);
	pthread_mutex_lock(&data->eat_lock);
	while (++i < data->nb_philo)
	{
		if (data->philos[i].meals_eaten >= data->meals_to_eat)
			meals++;
	}
	pthread_mutex_unlock(&data->eat_lock);
	return (meals == data->nb_philo);
}

int	check_dead(t_data *data)
{
	int	dead_phi;

	dead_phi = 0;
	pthread_mutex_lock(&data->dead_lock);
	dead_phi = data->dead;
	pthread_mutex_unlock(&data->dead_lock);
	return (dead_phi);
}

void	check_stop(t_data *data)
{
	int			i;
	long long	starving;

	while (!check_dead(data) && !check_meals(data))
	{
		i = -1;
		while (++i < data->nb_philo)
		{	
			pthread_mutex_lock(&data->eat_lock);
			starving = ft_get_time() - data->philos[i].t_last_meal;
			pthread_mutex_unlock(&data->eat_lock);
			if ((starving) > data->t_die)
			{
				write_message("died", data->philos[i].id, data);
				pthread_mutex_lock(&data->dead_lock);
				data->dead = 1;
				pthread_mutex_unlock(&data->dead_lock);
				break ;
			}
			if (check_meals(data))
				break ;
			ft_usleep(1, data);
		}
		if (check_meals(data))
			break ;
	}
}

void	process_eating(t_philo *philos)
{
	if (philos->id % 2)
	{
		pthread_mutex_lock(&philos->data->forks[philos->right_fork]);
		write_message("has taken a fork", philos->id, philos->data);
		pthread_mutex_lock(&philos->data->forks[philos->left_fork]);
		write_message("has taken a fork", philos->id, philos->data);
	}
	else
	{
		pthread_mutex_lock(&philos->data->forks[philos->left_fork]);
		write_message("has taken a fork", philos->id, philos->data);
		pthread_mutex_lock(&philos->data->forks[philos->right_fork]);
		write_message("has taken a fork", philos->id, philos->data);
	}
	write_message("is eating", philos->id, philos->data);
	pthread_mutex_lock(&philos->data->eat_lock);
	philos->t_last_meal = ft_get_time();
	philos->meals_eaten++;
	pthread_mutex_unlock(&philos->data->eat_lock);
	ft_usleep(philos->data->t_eat, philos->data);
	pthread_mutex_unlock(&philos->data->forks[philos->left_fork]);
	pthread_mutex_unlock(&philos->data->forks[philos->right_fork]);
}

void	*routine(void *arg)
{
	t_philo		*philos;

	philos = (t_philo *) arg;
	if (philos->id % 2)
		usleep(philos->data->t_eat / 2);
	while (!check_dead(philos->data) && philos->meals_eaten < philos->data->meals_to_eat)
	{
		process_eating(philos);
		write_message("is sleeping", philos->id, philos->data);
		ft_usleep(philos->data->t_sleep, philos->data);
		write_message("is thinking", philos->id, philos->data);
		usleep(100);
	}
	return (NULL);
}
