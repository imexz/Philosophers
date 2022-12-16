/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 20:26:46 by mstrantz          #+#    #+#             */
/*   Updated: 2022/01/16 17:21:52 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_pthread_mutex_init(struct s_philo *philo, struct s_mutex *mutexes)
{
	int	i;

	mutexes->forks = (pthread_mutex_t *) malloc(sizeof
			(pthread_mutex_t) * philo->data->n_philo);
	if (mutexes->forks == NULL)
		return (-1);
	pthread_mutex_init(&(mutexes->status), NULL);
	pthread_mutex_init(&(mutexes->time_death), NULL);
	pthread_mutex_init(&(mutexes->n_eaten), NULL);
	i = 0;
	while (i < philo->data->n_philo)
	{
		pthread_mutex_init(&(mutexes->forks[i]), NULL);
		philo[i].mutexes = mutexes;
		i++;
	}
	return (0);
}

void	ft_pthread_mutex_destroy(struct s_philo *philo)
{
	int	i;

	pthread_mutex_destroy(&philo->mutexes->n_eaten);
	pthread_mutex_destroy(&philo->mutexes->status);
	pthread_mutex_destroy(&philo->mutexes->time_death);
	i = 0;
	while (i < philo->data->n_philo)
	{
		pthread_mutex_destroy(philo->mutexes->forks + i);
		i++;
	}
}
