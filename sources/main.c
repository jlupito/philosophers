/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:18:11 by jarthaud          #+#    #+#             */
/*   Updated: 2023/05/23 12:22:01 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_data	*data)
{
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	init_philos(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].status = 0;
		data->philos[i].eating = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
	}
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	data->philos[0].left_fork = &data->forks[0];
	data->philos[0].right_fork = &data->forks[data->nb_philo - 1];
	i = 0;
	while (++i < data->nb_philo)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[i - 1];
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(ac, av))
		return (write(2, "Invalid arguments\n", 18), 1);
	save_args(ac, av, &data);
	data.tid = malloc(sizeof(pthread_t) * data.nb_philo);
	if (!data.tid)
		return (free_all(&data), 1);
	data.forks = malloc(sizeof(pthread_mutex_t) * data.nb_philo);
	if (!data.forks)
		return (free_all(&data), 1);
	data.philos = malloc(sizeof(t_philo) * data.nb_philo);
	if (!data.philos)
		return (free_all(&data), 1);
	init_philos(&data);
	process_philo(&data);
	return (0);
}
