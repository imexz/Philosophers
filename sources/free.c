/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 12:28:26 by mstrantz          #+#    #+#             */
/*   Updated: 2021/11/01 17:55:44 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_s_philo_free(struct s_philo *philo)
{
	int	i;

	if (philo)
	{
		if (philo->mutexes->forks != NULL)
		{
			i = 0;
			while (i < philo->data->n_philo)
			{
				free(philo->mutexes->forks);
				philo[i].mutexes->forks = NULL;
				i++;
			}
		}
		free(philo);
		philo = NULL;
	}
}
