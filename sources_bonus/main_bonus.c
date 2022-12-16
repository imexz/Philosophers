/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:23:31 by mstrantz          #+#    #+#             */
/*   Updated: 2022/01/15 20:16:55 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_input_check(int argc, char **argv, struct s_data *data)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (ft_s_data_parse(argc, argv, data) == 1)
		return (1);
	return (0);
}

static void	ft_s_philo_init(struct s_data *data, struct s_philo *philo)
{
	philo->time_death = (long) data->time_die;
	philo->n_eaten = 0;
	philo->status = THINK;
	philo->data = data;
	philo->start_time = 0;
}

static void	ft_create_childs(struct s_data *data, struct s_philo *philo)
{
	int		i;
	pid_t	pid;

	i = 1;
	while (i < data->n_philo + 1)
	{
		pid = fork();
		if (pid < 0)
		{
			kill(0, SIGINT);
			ft_semaphores_close(data);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			ft_philo(philo, data, i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	struct s_data	data;
	struct s_philo	philo;
	int				i;

	ft_semaphores_unlink();
	if (ft_input_check(argc, argv, &data))
		return (1);
	ft_s_philo_init(&data, &philo);
	ft_semaphores_init(&data);
	ft_create_childs(&data, &philo);
	i = 0;
	while (i++ < data.n_philo)
		sem_post(data.sem_start);
	i = 0;
	while (i++ < data.n_philo)
		waitpid(0, NULL, 0);
	ft_semaphores_close(&data);
	return (0);
}
