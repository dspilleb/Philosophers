/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:42:23 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/05 16:12:07 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	check_philos(t_data	*data)
{
	int	i;

	while (data->state)
	{
		i = -1;
		while (data->state && ++i < data->philo_count)
		{
			if (is_dead(i, data) && data->philos[i].pstate == ALIVE)
			{
				pthread_mutex_lock(&data->talk);
				printf(R "%d %d died\n" C, get_time(), i + 1);
				data->state = 0;
				pthread_mutex_unlock(&data->talk);
				pthread_exit(EXIT_SUCCESS);
			}
		}
	}
	pthread_exit(EXIT_SUCCESS);
}

void	destroy_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->talk);
}

void	unlock_mutex_exit(void *talk, void *fork1, void *fork2)
{
	if (talk)
		pthread_mutex_unlock(talk);
	if (fork1)
		pthread_mutex_unlock(fork1);
	if (fork2)
		pthread_mutex_unlock(fork2);
	pthread_exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	int		ret;
	t_data	data;

	ret = 0;
	if (ac == 5 || ac == 6)
	{
		if (init_data(ac, av, &data))
			return (EXIT_FAILURE);
		if (init_forks(&data))
			return (EXIT_FAILURE);
		ret = init_philosophers(&data);
		destroy_forks(&data);
	}
	else
		return (printf(R "Wrong number of arguments\n" C), 1);
	return (ret);
}
