/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:26:34 by jarthaud          #+#    #+#             */
/*   Updated: 2023/09/07 15:42:15 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

void	write_message(char *str, t_philo *philos)
{
	if (check_dead(philos->data) || check_meals(philos->data))
		return ;
	pthread_mutex_lock(&philos->data->write_lock);
	printf("%lld %d %s\n", ft_get_time() - philos->data->t_start,
		philos->id, str);
	pthread_mutex_unlock(&philos->data->write_lock);
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
