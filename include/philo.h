/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:58:45 by jarthaud          #+#    #+#             */
/*   Updated: 2023/09/07 15:33:34 by jarthaud         ###   ########.fr       */
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

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				nb_eaten;
	int				nb_to_eat;
	int				right_fork;
	int				left_fork;
	long long		t_last_meal;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				nb_to_eat;
	int				nb_eaten;
	int				dead;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	long long		t_start;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	write_lock;
}	t_data;

int			init_data(char **av, t_data *data);
int			init_mutex(t_data *data);
int			init_philos(t_data *data);
int			init_all(t_data *data, char **av);
int			process_philo(t_data *data);
void		process_eating(t_philo *philos);
void		*routine(void *arg);
long long	ft_get_time(void);
void		ft_usleep(long long time_ms, t_data *data);
int			ft_atoi(char *nptr);
int			check_args(int ac, char **av);
void		write_message(char *str, t_philo *philos);
int			check_meals(t_data *data);
int			check_dead(t_data *data);
void		check_stop(t_data *data);
void		solo_philo(t_data *data);
void		dies(int i, t_data *data);
long long	check_t_last_eat(t_philo *philos);
void		free_all(t_data *data);
void		free_destroy(t_data	*data);

#endif
