/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:18:11 by jarthaud          #+#    #+#             */
/*   Updated: 2023/06/29 10:24:37 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_data	*data)
{
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	*routine(void *arg)
{
	t_philo		*philos;

	philos = (t_philo *) arg;
	if (philos->id % 2)
		usleep(philos->data->t_eat / 2);
	while (1)
	{
		process_eating(philos);
		if (philos->data->dead || philos->nb_ate == philos->data->nb_to_eat)
			break ;
		write_message("is sleeping", philos->id, philos->data);
		ft_usleep(philos->data->t_sleep, philos->data);
		write_message("is thinking", philos->id, philos->data);
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
		solo_philo(data->philos[0], data);
	else
	{
		while (++i < data->nb_philo)
			pthread_create(&data->philos[i].t1, NULL,
				&routine, &data->philos[i]);
		check_stop(data);
		i = -1;
		while (++i < data->nb_philo)
			pthread_join(data->philos[i].t1, NULL);
		i = -1;
	}
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->eat_lock);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(ac, av))
		return (write(2, "Invalid arguments\n", 18), 1);
	init_data(ac, av, &data);
	data.forks = malloc(sizeof(pthread_mutex_t) * data.nb_philo);
	if (!data.forks)
		return (free_all(&data), 1);
	data.philos = malloc(sizeof(t_philo) * data.nb_philo);
	if (!data.philos)
		return (free_all(&data), 1);
	init_philos(&data);
	process_philo(&data);
	free_all(&data);
	return (0);
}
