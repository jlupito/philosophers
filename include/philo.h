/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:58:45 by jarthaud          #+#    #+#             */
/*   Updated: 2023/06/20 15:23:16 by jarthaud         ###   ########.fr       */
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
# include <sys/time.h>

// struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				meals_eaten;
	int				right_fork;
	int				left_fork;
	// int				status;
	// int				eating;
	// pthread_mutex_t	lock;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				meals_to_eat;
	pthread_mutex_t	dead_lock;
	int				dead;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	long			time_start;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	// int				completed_times_eat;
	// pthread_t		*tid;
}	t_data;

void		init_data(int ac, char **av, t_data *data);
void		init_philos(t_data *data);
int			process_philo(t_data *data);
int			ft_atoi(char *nptr);
long long	ft_get_time(void);
int			check_args(int ac, char **av);
void		write_message(char *str, int id, t_data *data);
void		ft_usleep(long long time_ms);
long long	ft_get_time(void);
void		*routine(void *arg);

#endif