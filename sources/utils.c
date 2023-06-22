/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:26:34 by jarthaud          #+#    #+#             */
/*   Updated: 2023/06/21 17:07:55 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long int ft_get_time()
{
	struct timeval tv;
	long int start_time;
	
	gettimeofday(&tv, NULL);
	start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (start_time);
}

void	ft_usleep(long int time_ms)
{
	long int	start;
	
	start = ft_get_time();
	while ((ft_get_time() - start) < time_ms)
		usleep(time_ms / 10);
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
		