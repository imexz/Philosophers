/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:58:41 by mstrantz          #+#    #+#             */
/*   Updated: 2022/01/15 18:49:34 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_s_data_init_input(struct s_data *data, int i, int value)
{
	if (i == 1)
		data->n_philo = value;
	if (i == 2)
		data->time_die = value;
	if (i == 3)
		data->time_eat = value;
	if (i == 4)
		data->time_slp = value;
	if (i == 5)
		data->n_dishes = value;
}

int	ft_s_data_parse(int argc, char **argv, struct s_data *data)
{
	int		i;
	int		number;

	i = 1;
	while (i < argc)
	{
		if (ft_isint(argv[i], &number) == 1)
			ft_s_data_init_input(data, i, number);
		else
			return (1);
		i++;
	}
	if (argc == 5)
		data->n_dishes = -1;
	if (data->n_philo < 1 || data->time_die < 0 || data->time_eat < 0
		|| data->time_slp < 0 || data->n_dishes < -1)
		return (1);
	return (0);
}
