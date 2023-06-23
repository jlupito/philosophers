/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:58:45 by jarthaud          #+#    #+#             */
/*   Updated: 2023/06/23 16:27:57 by jarthaud         ###   ########.fr       */
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
	int				meals_eaten;
	int				right_fork;
	int				left_fork;
	long int		time_last_eaten;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				meals_to_eat;
	pthread_mutex_t	dead_lock;
	int				dead;
	int				stop;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	long int		time_start;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
}	t_data;

void		init_data(int ac, char **av, t_data *data);
void		init_philos(t_data *data);
int			process_philo(t_data *data);
void		process_eating(t_philo *philos);
void		*routine(void *arg);
long int	ft_get_time(void);
void		ft_usleep(long int time_ms, t_data *data);
int			ft_atoi(char *nptr);
int			check_args(int ac, char **av);
void		write_message(char *str, int id, t_data *data);

#endif
