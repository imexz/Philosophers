/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:23:54 by mstrantz          #+#    #+#             */
/*   Updated: 2022/01/16 00:14:16 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/types.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

# define SEM_FORKS "/sem_forks"
# define SEM_STATUS "/sem_status"
# define SEM_START "/sem_start"
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
	struct s_data	*data;
};

struct s_data
{
	int			n_philo;
	int			time_die;
	int			time_eat;
	int			time_slp;
	int			n_dishes;
	sem_t		*sem_forks;
	sem_t		*sem_status;
	sem_t		*sem_start;
};

int				ft_isint(char *str, int *number);
int				ft_s_data_parse(int argc, char **argv, struct s_data *data);
void			ft_philo(struct s_philo *philo, struct s_data *data, size_t id);
void			ft_update_status(struct s_philo *philo, int status, char *msg);
long			ft_get_timestamp(struct s_philo *philo);
void			ft_semaphores_init(struct s_data *data);
void			ft_semaphores_close(struct s_data *data);
void			ft_semaphores_unlink(void);

#endif