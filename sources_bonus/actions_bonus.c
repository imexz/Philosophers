/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:38:46 by mstrantz          #+#    #+#             */
/*   Updated: 2022/01/16 00:24:52 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_get_timestamp(struct s_philo *philo)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == 0)
	{
		if (philo->start_time != 0)
			return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
				- philo->start_time);
		return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	}
	return (-1);
}

void	ft_update_status(struct s_philo *philo, int status, char *msg)
{
	long	time;

	if (status == END_SIM)
		return ;
	if (philo->status != END_SIM)
	{
		sem_wait(philo->data->sem_status);
		time = ft_get_timestamp(philo);
		if (time == -1)
		{
			ft_update_status(philo, END_SIM, NULL);
			return ;
		}
		if (status == EAT)
			philo->time_death = time + (long) philo->data->time_die;
		if (philo->status != END_SIM)
			philo->status = status;
		if (philo->status != END_SIM)
			printf("%ld %d %s\n", time, philo->th_id, msg);
		if (status == SLEEP)
			philo->n_eaten++;
		sem_post(philo->data->sem_status);
	}
}
