/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:58:57 by jarthaud          #+#    #+#             */
/*   Updated: 2023/06/29 10:07:31 by jarthaud         ###   ########.fr       */
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

void	init_data(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->nb_to_eat = -1;
	if (ac == 6)
		data->nb_to_eat = ft_atoi(av[5]);
	data->dead = 0;
	data->t_start = 0;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
}

void	init_philos(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].nb_ate = 0;
		data->philos[i].t_last_meal = ft_get_time();
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = i + 1;
		if (i == data->nb_philo - 1)
			data->philos[i].right_fork = 0;
		pthread_mutex_init(&data->forks[i], NULL);
	}
}
