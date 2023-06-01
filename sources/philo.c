/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:58:57 by jarthaud          #+#    #+#             */
/*   Updated: 2023/06/01 15:45:13 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *data)
{
	int i;

	i = -1;
	while (++i < 1000000)
	{
		pthread_mutex_lock(&lock);
			cont++;
		pthread_mutex_unlock(&lock);
	}
	return (NULL);
}

int	process_philo(t_data *data)
{
	int			i;
	pthread_t	t1;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_create(&data->philos[i].t1, NULL, &routine, NULL);
	}
	pthread_join(t1, NULL);
	pthread_mutex_destroy(&data);
	printf("cont: %d\n", );
}
