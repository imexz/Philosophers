/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:38:46 by mstrantz          #+#    #+#             */
/*   Updated: 2022/01/17 14:20:57 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_forks(struct s_philo *philo)
{
	if (philo->th_id == 1)
	{
		pthread_mutex_lock(&philo->mutexes->forks[philo->th_id - 1]);
		ft_update_status(philo, FORK, "has taken a fork");
		pthread_mutex_lock(&philo->mutexes->forks[philo->data->n_philo - 1]);
		ft_update_status(philo, FORK, "has taken a fork");
	}
	else
	{
		if ((philo->th_id - 1) % 2 == 0)
		{
			pthread_mutex_lock(&philo->mutexes->forks[philo->th_id - 1]);
			ft_update_status(philo, FORK, "has taken a fork");
			pthread_mutex_lock(&philo->mutexes->forks[philo->th_id - 2]);
			ft_update_status(philo, FORK, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(&philo->mutexes->forks[philo->th_id - 2]);
			ft_update_status(philo, FORK, "has taken a fork");
			pthread_mutex_lock(&philo->mutexes->forks[philo->th_id - 1]);
			ft_update_status(philo, FORK, "has taken a fork");
		}
	}
}

void	ft_drop_forks(struct s_philo *philo)
{
	if (philo->th_id == 1)
	{
		pthread_mutex_unlock(&philo->mutexes->forks[philo->th_id - 1]);
		pthread_mutex_unlock(&philo->mutexes->forks[philo->data->n_philo - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->mutexes->forks[philo->th_id - 1]);
		pthread_mutex_unlock(&philo->mutexes->forks[philo->th_id - 2]);
	}
}

static void	ft_s_philo_status_end_sim(struct s_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philo)
	{
		philo[i].status = END_SIM;
		i++;
	}
}

static void	ft_set_status_eat(struct s_philo *philo, long time)
{
	pthread_mutex_lock(&philo->mutexes->time_death);
	philo->time_death = time + (long) philo->data->time_die;
	pthread_mutex_unlock(&philo->mutexes->time_death);
}

void	ft_update_status(struct s_philo *philo, int status, char *msg)
{
	long	time;

	if (status == END_SIM)
		ft_s_philo_status_end_sim(philo);
	if (status == END_SIM)
		return ;
	if (philo->status != END_SIM)
	{
		pthread_mutex_lock(&philo->mutexes->status);
		time = ft_get_timestamp(philo);
		if (time == -1)
			ft_update_status(philo, END_SIM, NULL);
		if (status == EAT)
			ft_set_status_eat(philo, time);
		if (philo->status != END_SIM)
			philo->status = status;
		if (philo->status != END_SIM)
			printf("%ld %d %s\n", time, philo->th_id, msg);
		if (status == SLEEP)
			philo->n_eaten++;
		pthread_mutex_unlock(&philo->mutexes->status);
	}
}
