/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:26:34 by jarthaud          #+#    #+#             */
/*   Updated: 2023/06/28 14:14:27 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	solo_philo(t_philo philos, t_data *data)
{
	write_message("has taken a fork", philos.id, data);
	ft_usleep(data->t_die, data);
	write_message("died", philos.id, data);
}

long long	ft_get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long long time_ms, t_data *data)
{
	long long	time;

	time = ft_get_time();
	while (!check_dead(data) && !check_meals(data))
	{
		if (ft_get_time() - time >= time_ms)
			break ;
		usleep(10);
	}
}

void	write_message(char *str, int id, t_data *data)
{
	long long	time;

	if (!data->dead)
	{
		pthread_mutex_lock(&data->write_lock);
		time = ft_get_time() - data->t_start;
		printf("%lld %d %s\n", time, id, str);
		pthread_mutex_unlock(&data->write_lock);
	}
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
