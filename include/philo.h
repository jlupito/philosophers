/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:58:45 by jarthaud          #+#    #+#             */
/*   Updated: 2023/05/22 16:22:19 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <bsd/string.h>
# include <fcntl.h>
# include <stdarg.h>
# include <pthread.h>

// struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_count;
	int				status;
	int				eating;
	int				time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				nb_times_eat;
	int				completed_times_eat;
	int				dead;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_start;
	t_philo			*philos;
	pthread_t		*tid;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

void	save_args(int ac, char **av, t_data *data);
void	init_philos(t_data *data);
int		ft_atoi(char *nptr);
int		check_args(int ac, char **av);
void	init_forks(t_data *data);

#endif