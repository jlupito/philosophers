/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:58:57 by jarthaud          #+#    #+#             */
/*   Updated: 2023/06/02 12:16:12 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *data)
{
	pthread_mutex_lock(&write);
	pthread_mutex_lock(&forks[data->nb_philo]);
	pthread_mutex_lock(&forks[data->nb_philo - 1]);
	pthread_mutex_unlock(&forks[]);
	pthread_mutex_unlock(&forks[]);
	pthread_mutex_unlock(&write);
	return (NULL);
}

int	process_philo(t_data *data)
{
	int			i;
	pthread_t	t1;

	i = -1;
	while (++i < data->nb_philo)
		pthread_create(&data->philos[i].t1, NULL, &routine, &data->philos[i]);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->philos[i].t1, NULL);
	pthread_mutex_destroy(&data);
}
