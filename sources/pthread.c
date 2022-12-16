/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:35:03 by mstrantz          #+#    #+#             */
/*   Updated: 2022/01/17 14:23:59 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_n_philo(struct s_philo *philo)
{
	if (philo->data->n_philo == 1)
	{
		philo->start_time = philo->data->start_time;
		ft_update_status(philo, THINK, "is thinking");
		ft_update_status(philo, FORK, "has taken a fork");
		usleep(philo->data->time_die * 1000 + 300);
		while (philo->status != END_SIM)
			continue ;
		return (1);
	}
	return (0);
}

void	*th_philo(void *arg)
{
	struct s_philo		*philo;

	philo = arg;
	if (ft_syncronize_threads(philo))
		return (NULL);
	if (ft_check_n_philo(philo) == 1)
		return (NULL);
	philo->start_time = philo->data->start_time;
	if (philo->th_id % 2 == 0)
		usleep(7500);
	while (philo->status != END_SIM)
	{
		ft_update_status(philo, THINK, "is thinking");
		ft_take_forks(philo);
		ft_update_status(philo, EAT, "is eating");
		if (philo->status == EAT)
			ft_usleep(philo->data->time_eat, philo);
		ft_update_status(philo, SLEEP, "is sleeping");
		ft_drop_forks(philo);
		if (philo->status == SLEEP)
			ft_usleep(philo->data->time_slp, philo);
	}
	return (NULL);
}

static void	ft_deathangel(struct s_philo *philo)
{
	int		i;
	long	time;

	i = 0;
	while (i < philo->data->n_philo)
	{
		pthread_mutex_lock(&philo->mutexes->status);
		time = ft_get_timestamp(philo);
		if (philo[i].time_death < time)
		{
			ft_update_status(philo, END_SIM, NULL);
			printf("%ld %d died\n", time, philo[i].th_id);
			break ;
		}
		pthread_mutex_unlock(&philo->mutexes->status);
		i++;
	}
}

void	*ft_supervisor_death(void *arg)
{
	struct s_philo	*philo;

	philo = arg;
	usleep(philo->data->time_die * 1000);
	if (philo->data->start_sim == -1)
		return (NULL);
	while (philo->status != END_SIM)
	{
		ft_deathangel(philo);
	}
	return (NULL);
}

void	*ft_supervisor_eaten(void *arg)
{
	struct s_philo	*philo;
	int				i;
	int				passed;

	philo = arg;
	usleep(philo->data->time_die * 1000);
	if (philo->data->start_sim == -1)
		return (NULL);
	while (philo->status != END_SIM)
	{
		i = 0;
		passed = 1;
		while (i < philo->data->n_philo)
		{
			if (philo[i].n_eaten < philo[i].data->n_dishes)
				passed = 0;
			i++;
		}
		if (passed)
		{
			ft_update_status(philo, END_SIM, NULL);
			break ;
		}
	}
	return (NULL);
}
