/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:07:07 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/05 13:20:44 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_unsigned_int(char **av)
{
	int	j;
	int	i;

	j = 0;
	while (av[++j])
	{
		i = -1;
		while (av[j][++i])
		{
			if (!((av[j][i] >= '0' && av[j][i] <= '9') || av[j][i] == '+'))
				return (EXIT_FAILURE);
			if (av[j][i] == '+' && (i != 0 || !av[j][i + 1]))
				return (EXIT_FAILURE);
		}
		if (i == 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	number;

	number = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10;
		number = number + nptr[i] - 48;
		i++;
		if (number * sign > 2147483647 || number * sign < -2147483648)
			errno = 22;
	}
	return (number * sign);
}
