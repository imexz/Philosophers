/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:30:17 by mstrantz          #+#    #+#             */
/*   Updated: 2022/01/17 00:13:54 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_skip_ws_get_sign_get_digits(const char *str, int *i, int *sign)
{
	int	idx;

	while ((str[*i] >= '\t' && str[*i] <= '\r') || str[*i] == ' ')
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = (-1);
		(*i)++;
	}
	while (str[*i] == '0')
		(*i)++;
	idx = *i;
	while (str[idx] <= '9' && str[idx] >= '0')
		idx++;
	if (str[idx] != '\0')
		return (-1);
	if (idx > *i)
		return (idx);
	if ((idx > 0 && str[idx - 1] != '0') || idx == 0)
		return (-1);
	return (0);
}

static void	ft_get_int(int sign, int *number, char *str)
{
	int	i;
	int	digit;
	int	res;

	i = 0;
	digit = 0;
	res = 0;
	while (str[i] <= '9' && str[i] >= '0')
	{
		digit++;
		res *= 10;
		res += (str[i] - '0');
		i++;
	}
	*number = (sign * res);
}

static int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i] || (str1[i] == 0) || str2[i] == 0)
			return (((unsigned char *) str1)[i] - ((unsigned char *) str2)[i]);
		i++;
	}
	return (0);
}

static int	ft_cmp_max_min_string(char *str, int sign)
{
	char	*max_int;
	char	*min_int;

	max_int = "2147483647";
	min_int = "2147483648";
	if (sign == 1)
	{
		if (ft_strncmp(max_int, str, 10) < 0)
			return (0);
		return (1);
	}
	else
	{
		if (ft_strncmp(min_int, str, 10) < 0)
			return (0);
		return (1);
	}
}

int	ft_isint(char *str, int *number)
{
	int	i;
	int	sign;
	int	digits;

	if (str)
	{
		i = 0;
		sign = 1;
		*number = 0;
		digits = ft_skip_ws_get_sign_get_digits(str, &i, &sign);
		if (digits == 0)
			return (1);
		else if (digits < 0 || digits > 10)
			return (0);
		else if (digits <= 10)
		{
			if (digits == 10 && ft_cmp_max_min_string(str + i, sign) == 0)
				return (0);
			ft_get_int(sign, number, str + i);
			return (1);
		}
	}
	return (0);
}
