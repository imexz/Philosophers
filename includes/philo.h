/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:28:18 by mstrantz          #+#    #+#             */
/*   Updated: 2022/01/17 00:16:01 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define THINK 0
# define EAT 1
# define SLEEP 2
# define FORK 3
# define END_SIM 4

struct s_philo
{
	int				n_eaten;
	pthread_t		pth;
	int				th_id;
	char			status;
	long			time_death;
	long			start_time;
	struct s_mutex	*mutexes;
	struct s_data	*data;
};

struct s_mutex
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	status;
	pthread_mutex_t	time_death;
	pthread_mutex_t	n_eaten;
};

struct s_data
{
	int			n_philo;
	int			time_die;
	int			time_eat;
	int			time_slp;
	int			n_dishes;
	int			start_sim;
	long		start_time;
};

int				ft_isint(char *str, int *number);
int				ft_s_data_parse(int argc, char **argv, struct s_data *data);
struct s_philo	*ft_s_philo_init(struct s_data *data);
int				ft_pthread_mutex_init(struct s_philo *philo, \
					struct s_mutex *mutexes);
pthread_t		*ft_pthread_t_create(struct s_philo *philo);
int				ft_syncronize_threads(struct s_philo *philo);
void			*th_philo(void *arg);
void			ft_take_forks(struct s_philo *philo);
void			ft_drop_forks(struct s_philo *philo);
void			ft_update_status(struct s_philo *philo, int status, char *msg);
void			ft_usleep(long duration, struct s_philo *philo);
long			ft_get_timestamp(struct s_philo *philo);
void			*ft_supervisor_death(void *arg);
void			*ft_supervisor_eaten(void *arg);
void			ft_pthread_t_join(struct s_philo *philo,
					pthread_t *supervisors);
void			ft_pthread_mutex_destroy(struct s_philo *philo);
void			ft_s_philo_free(struct s_philo *philo);

#endif