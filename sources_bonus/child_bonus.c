/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 23:04:57 by mstrantz          #+#    #+#             */
/*   Updated: 2022/01/17 14:31:46 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_usleep(long duration, struct s_philo *philo)
{
	long	now;
	long	end;
	int		usec;

	now = ft_get_timestamp(philo);
	end = now + duration;
	usec = 125;
	if (philo->data->n_philo >= 30)
		usec = 750;
	while (1)
	{
		if (ft_get_timestamp(philo) >= end)
			break ;
		usleep(usec);
	}
}

static void	*philo_loop(void *arg)
{
	struct s_philo	*philo;

	philo = arg;
	sem_wait(philo->data->sem_start);
	philo->start_time = ft_get_timestamp(philo);
	philo->time_death = philo->data->time_die;
	while (philo->status != END_SIM)
	{
		ft_update_status(philo, THINK, "is thinking");
		if (philo->data->n_philo == 1)
			ft_update_status(philo, FORK, "has taken a fork");
		sem_wait(philo->data->sem_forks);
		ft_update_status(philo, FORK, "has taken a fork");
		ft_update_status(philo, FORK, "has taken a fork");
		ft_update_status(philo, EAT, "is eating");
		if (philo->status == EAT)
			ft_usleep(philo->data->time_eat, philo);
		sem_post(philo->data->sem_forks);
		ft_update_status(philo, SLEEP, "is sleeping");
		if (philo->status == SLEEP)
			ft_usleep(philo->data->time_slp, philo);
	}
	return (NULL);
}

static void	ft_supervisor(struct s_philo *philo)
{
	long			time;

	usleep(philo->data->time_die * 1000);
	while (philo->status != END_SIM)
	{
		sem_wait(philo->data->sem_status);
		time = ft_get_timestamp(philo);
		if (philo->time_death < time)
		{
			printf("%ld %d died\n", time, philo->th_id);
			kill(0, SIGINT);
			break ;
		}
		sem_post(philo->data->sem_status);
		if (philo->data->n_dishes != -1 \
				&& philo->n_eaten >= philo->data->n_dishes)
		{
			philo->status = END_SIM;
			break ;
		}
	}
}

void	ft_philo(struct s_philo *philo, struct s_data *data, size_t id)
{
	pthread_t	philo_thread;

	philo->th_id = id;
	if (pthread_create(&philo_thread, NULL, &philo_loop, philo) != 0)
	{
		ft_semaphores_close(data);
		kill(0, SIGINT);
		exit(EXIT_FAILURE);
	}
	pthread_detach(philo_thread);
	ft_supervisor(philo);
	pthread_join(philo_thread, NULL);
	exit(EXIT_SUCCESS);
}
