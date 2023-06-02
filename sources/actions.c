/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:39:58 by jarthaud          #+#    #+#             */
/*   Updated: 2023/06/02 16:06:35 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void 	write_message(char *str, t_philo *philos)
{
	long	time;

	time = ft_get_time();
	pthread_mutex_lock(&philos->data->write);
	printf("");
	pthread_mutex_unlock(&philos->data->write);
}

void	take_forks(t_philo philos)
{
	pthread_mutex_lock(&forks[data->nb_philo]);
	pthread_mutex_unlock(&forks[]);
}

void	leave_forks(t_philo philos)
{
	pthread_mutex_lock(&forks[data->nb_philo]);
	pthread_mutex_unlock(&forks[]);
}

void	eat_sleep(t_data *data)
{
	take_forks
	eat
	write eat
	usleep time
	leave fork
	count 1 meal
	sleep
	write sleep
	usleep time
	think
	write think
	
	
}