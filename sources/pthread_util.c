/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:31:52 by mstrantz          #+#    #+#             */
/*   Updated: 2022/01/16 23:57:44 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_syncronize_threads(struct s_philo *philo)
{
	int	ret;

	while (1)
	{
		if (philo->data->start_sim == 1)
		{
			ret = 0;
			break ;
		}
		else if (philo->data->start_sim == -1)
		{
			ret = 1;
			break ;
		}
	}
	return (ret);
}

static pthread_t	*ft_pthread_t_create_supervisors(struct s_philo *philo)
{
	pthread_t	*supervisors;

	supervisors = (pthread_t *)malloc(sizeof(pthread_t) * 2);
	if (supervisors == NULL)
		return (NULL);
	if (pthread_create(&supervisors[0], NULL, &ft_supervisor_death, philo) != 0)
	{
		free(supervisors);
		return (NULL);
	}
	supervisors[1] = NULL;
	if (philo->data->n_dishes != -1)
	{
		if (pthread_create(&supervisors[1], NULL,
				&ft_supervisor_eaten, philo) != 0)
		{
			free(supervisors);
			return (NULL);
		}
	}
	return (supervisors);
}

static void	pthread_create_error(struct s_philo *philo, \
									pthread_t	*supervisors, int i)
{
	while (i > 0)
	{
		philo->data->start_sim = -1;
		pthread_join(philo[--i].pth, NULL);
	}
	pthread_join(supervisors[0], NULL);
	if (supervisors[1] != NULL)
		pthread_join(supervisors[0], NULL);
	free(supervisors);
}

pthread_t	*ft_pthread_t_create(struct s_philo *philo)
{
	pthread_t	*supervisors;
	int			i;

	supervisors = ft_pthread_t_create_supervisors(philo);
	if (supervisors == NULL)
		return (NULL);
	i = 0;
	while (i < philo->data->n_philo)
	{
		if (pthread_create(&philo[i].pth, NULL, &th_philo, philo + i) != 0)
		{
			pthread_create_error(philo, supervisors, i);
			return (NULL);
		}
		i++;
	}
	philo->data->start_time = ft_get_timestamp(philo);
	philo->data->start_sim = 1;
	return (supervisors);
}

void	ft_pthread_t_join(struct s_philo *philo, pthread_t *supervisors)
{
	int	i;

	pthread_join(supervisors[0], NULL);
	if (supervisors[1] != NULL)
		pthread_join(supervisors[1], NULL);
	free(supervisors);
	i = 0;
	while (i < philo->data->n_philo)
	{
		pthread_join(philo[i].pth, NULL);
		i++;
	}
}
