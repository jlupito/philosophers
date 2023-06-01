/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:18:11 by jarthaud          #+#    #+#             */
/*   Updated: 2023/06/01 14:45:23 by jarthaud         ###   ########.fr       */
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

void	init_data(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meals_to_eat = ft_atoi(av[5]);
	data->dead = 0;
	data->time_start = ft_get_time();
	pthread_mutex_init(&data->write, NULL);
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
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[data->nb_philo - i];
		pthread_mutex_init(&data->forks[i], NULL);
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(ac, av))
		return (write(2, "Invalid arguments\n", 18), 1);
	data.forks = malloc(sizeof(pthread_mutex_t) * data.nb_philo);
	if (!data.forks)
		return (free_all(&data), 1);
	data.philos = malloc(sizeof(t_philo) * data.nb_philo);
	if (!data.philos)
		return (free_all(&data), 1);
	init_data(ac, av, &data);
	init_philos(&data);
	process_philo(&data);
	return (0);
}
