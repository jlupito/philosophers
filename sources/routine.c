/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:39:58 by jarthaud          #+#    #+#             */
/*   Updated: 2023/09/07 15:42:42 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	dies(int i, t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_lock);
	pthread_mutex_lock(&data->write_lock);
	printf("%lld %d died\n", ft_get_time() - data->t_start,
		data->philos[i].id);
	pthread_mutex_unlock(&data->write_lock);
}

void	solo_philo(t_data *data)
{
	write_message("has taken a fork", data->philos);
	ft_usleep(data->t_die, data);
	write_message("died", data->philos);
}

void	*routine(void *arg)
{
	t_philo		*philos;

	philos = (t_philo *)arg;
	write_message("is thinking", philos);
	if (!(philos->id % 2))
		ft_usleep(philos->t_eat / 2, philos->data);
	while (!check_dead(philos->data) && !check_meals(philos->data))
	{
		process_eating(philos);
		write_message("is sleeping", philos);
		ft_usleep(philos->t_sleep, philos->data);
		write_message("is thinking", philos);
		usleep(100);
	}
	return (NULL);
}

int	process_philo(t_data *data)
{
	int	i;

	i = -1;
	data->t_start = ft_get_time();
	if (data->nb_philo == 1)
	{
		solo_philo(data);
		return (0);
	}
	while (++i < data->nb_philo)
		if (pthread_create(&data->philos[i].t1, NULL,
				&routine, &data->philos[i]))
			return (1);
	check_stop(data);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->philos[i].t1, NULL);
	return (0);
}
