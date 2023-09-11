/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:39:58 by jarthaud          #+#    #+#             */
/*   Updated: 2023/09/07 15:45:47 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_meals(t_data *data)
{
	int	meals;
	int	i;

	meals = 0;
	i = -1;
	if (data->nb_to_eat == -1)
		return (0);
	pthread_mutex_lock(&data->eat_lock);
	while (++i < data->nb_philo)
	{
		if (data->philos[i].nb_eaten >= data->philos->nb_to_eat)
			meals++;
	}
	pthread_mutex_unlock(&data->eat_lock);
	return (meals == data->nb_philo);
}

int	check_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead == 1)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

long long	check_t_last_eat(t_philo *philos)
{
	long long	starved;

	pthread_mutex_lock(&philos->data->dead_lock);
	starved = philos->t_last_meal;
	pthread_mutex_unlock(&philos->data->dead_lock);
	return (starved);
}

void	check_stop(t_data *data)
{
	int			i;

	while (!data->dead)
	{
		i = -1;
		while (++i < data->nb_philo)
		{	
			if (ft_get_time() - check_t_last_eat(&data->philos[i])
				>= data->t_die)
			{
				dies(data->philos[i].id, data);
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
