/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:58:57 by jarthaud          #+#    #+#             */
/*   Updated: 2023/06/23 14:37:08 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_data(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->meals_to_eat = -1;
	if (ac == 6)
		data->meals_to_eat = ft_atoi(av[5]);
	data->dead = 0;
	data->time_start = 0;
	data->stop = 0;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
}

void	init_philos(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].time_last_eaten = 0;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = i + 1;
		if (i == data->nb_philo - 1)
			data->philos[i].right_fork = 0;
		pthread_mutex_init(&data->forks[i], NULL);
	}
}
