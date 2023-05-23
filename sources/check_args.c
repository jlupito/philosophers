/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:26:34 by jarthaud          #+#    #+#             */
/*   Updated: 2023/05/22 17:09:36 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	save_args(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_times_eat = ft_atoi(av[5]);
	data->dead = 0;
	data->completed_times_eat = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
}

int	ft_atoi(char *nptr)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (nptr[i] && (nptr[i] == 9 || nptr[i] == 10 || nptr[i] == 11
			|| nptr[i] == 12 || nptr[i] == 13 || nptr[i] == 32))
		i++;
	if (nptr[i] == 45 || nptr[i] == 43)
	{
		if (nptr[i] == 45)
			sign = -sign;
		i++;
	}
	while (nptr[i] && (nptr[i] > 47 && nptr[i] < 58))
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	return (res * sign);
}

int check_args(int ac, char **av)
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
		