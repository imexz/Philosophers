/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:39:44 by mstrantz          #+#    #+#             */
/*   Updated: 2022/01/15 21:28:34 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_semaphores_init_part2(struct s_data *data, int ret)
{
	if (ret == 0)
	{
		data->sem_start = sem_open(SEM_START, O_CREAT, 0660, 0);
		if (data->sem_start == SEM_FAILED)
			ret = 3;
	}
	if (ret != 0)
	{
		if (ret != 0)
			write(2, "sem_open failed\n", 17);
		if (ret > 1)
			sem_unlink(SEM_FORKS);
		if (ret > 2)
			sem_unlink(SEM_STATUS);
		exit (EXIT_FAILURE);
	}
}

void	ft_semaphores_init(struct s_data *data)
{
	int	ret;

	ret = 0;
	data->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0660, data->n_philo / 2);
	if (data->sem_forks == SEM_FAILED)
		ret = 1;
	if (ret == 0)
	{
		data->sem_status = sem_open(SEM_STATUS, O_CREAT, 0660, 1);
		if (data->sem_status == SEM_FAILED)
			ret = 2;
	}
	ft_semaphores_init_part2(data, ret);
}

void	ft_semaphores_unlink(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_STATUS);
	sem_unlink(SEM_START);
}

void	ft_semaphores_close(struct s_data *data)
{
	int	flag;

	flag = 0;
	if (sem_close(data->sem_forks) < 0)
		flag = 1;
	if (sem_close(data->sem_status) < 0)
		flag = 1;
	if (sem_close(data->sem_start) < 0)
		flag = 1;
	if (flag == 1)
	{
		write(2, "sem_close failed\n", 18);
		ft_semaphores_unlink();
		exit(EXIT_FAILURE);
	}
	ft_semaphores_unlink();
}
