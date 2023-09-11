/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:58:57 by jarthaud          #+#    #+#             */
/*   Updated: 2023/09/07 15:45:39 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (1);
	ac--;
	while (ac > 0)
	{
		i = 0;
		while (av[ac][i])
		{
			if (av[ac][0] == '+')
				i++;
			if (av[ac][i] >= 48 && av[ac][i] <= 57)
				i++;
			else
				return (1);
		}
		if (ft_atoi(av[ac]) > 0)
			ac--;
		else
			return (1);
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int		i;

	i = -1;
	data->philos = malloc(sizeof(t_philo) * (data->nb_philo));
	if (!data->philos)
		return (free_all(data), 1);
	while (++i < data->nb_philo)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].t1 = 0;
		data->philos[i].nb_eaten = 0;
		data->philos[i].nb_to_eat = data->nb_to_eat;
		data->philos[i].t_last_meal = ft_get_time();
		data->philos[i].t_eat = data->t_eat;
		data->philos[i].t_die = data->t_die;
		data->philos[i].t_sleep = data->t_sleep;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->nb_philo;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->nb_philo];
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (free_all(data), 1);
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	return (0);
}

int	init_data(char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->nb_to_eat = -1;
	if (av[5])
		data->nb_to_eat = ft_atoi(av[5]);
	data->dead = 0;
	data->nb_eaten = 0;
	data->t_start = ft_get_time();
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	return (0);
}

int	init_all(t_data *data, char **av)
{
	if (!init_data(av, data))
		if (!init_mutex(data))
			if (!init_philos(data))
				return (0);
	return (1);
}
