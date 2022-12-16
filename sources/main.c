/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:23:31 by mstrantz          #+#    #+#             */
/*   Updated: 2021/11/03 18:47:26 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_usleep(long duration, struct s_philo *philo)
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

static int	ft_input_check(int argc, char **argv, struct s_data *data)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (ft_s_data_parse(argc, argv, data) == 1)
		return (2);
	return (0);
}

static struct s_philo	*ft_initialize(struct s_data *data,
		struct s_mutex *mutexes)
{
	struct s_philo	*philo;
	int				ret;

	philo = ft_s_philo_init(data);
	if (philo == NULL)
		return (NULL);
	ret = ft_pthread_mutex_init(philo, mutexes);
	if (ret == -1)
	{
		ft_s_philo_free(philo);
		return (NULL);
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	struct s_data	data;
	struct s_philo	*philo;
	pthread_t		*supervisors;
	struct s_mutex	mutexes;

	if (ft_input_check(argc, argv, &data) != 0)
		return (1);
	philo = ft_initialize(&data, &mutexes);
	if (philo == NULL)
		return (1);
	supervisors = ft_pthread_t_create(philo);
	if (supervisors == NULL)
	{
		ft_pthread_mutex_destroy(philo);
		ft_s_philo_free(philo);
		return (5);
	}
	ft_pthread_t_join(philo, supervisors);
	ft_pthread_mutex_destroy(philo);
	ft_s_philo_free(philo);
	return (0);
}
