/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:53:49 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/05 16:11:11 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_forks(t_data *data)
{
	int				i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			return (printf(R "Error Mutex\n" C), 1);
		}
	}
	return (0);
}

int	create_threads(int nb, t_data *data)
{
	int	i;

	i = -1;
	while (++i < nb)
	{
		if (!data->state)
			return (i);
		if (pthread_create(&data->philos[i].philo, \
		NULL, (void *)routine, (void *) &data->philos[i]))
		{
			pthread_mutex_lock(&data->talk);
			data->state = 0;
			printf(R "Failure to create philosophers\n" C);
			pthread_mutex_unlock(&data->talk);
			return (i);
		}
	}
	return (i);
}

int	init_philosophers(t_data *data)
{
	int			nb_threads;
	int			i;
	pthread_t	monitoring;

	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].pstate = ALIVE;
		data->philos[i].number = i + 1;
		data->philos[i].data = data;
	}
	if (pthread_create(&monitoring, NULL, (void *)check_philos, data))
		return (printf(R "Failure to create philosophers\n" C), 1);
	i = -1;
	nb_threads = create_threads(data->philo_count, data);
	while (++i < nb_threads)
		pthread_join(data->philos[i].philo, NULL);
	data->state = 0;
	pthread_join(monitoring, NULL);
	return (data->philo_count - i);
}

int	init_data(int ac, char **av, t_data *data)
{
	errno = 0;
	data->state = 1;
	data->must_eat = -1;
	if (is_unsigned_int(av))
		return (printf(R "Arguments aren't positive integers\n" C), 1);
	data->philo_count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	if (data->philo_count == 0 || data->time_to_die == 0 || \
	data->time_to_eat == 0 || data->time_to_sleep == 0 || data->must_eat == 0)
		return (printf(R "All values must be above 0\n" C), 1);
	if (data->philo_count > 500)
		return (printf(R "The number of philosophers must be under 500\n" C), 1);
	if (errno)
		return (printf(R "Arguments aren't positive integers\n" C), 1);
	if (pthread_mutex_init(&data->talk, NULL))
		return (printf(R "Error Mutex\n" C), 1);
	memset(data->last_meal, 0, (data->philo_count * sizeof(int)));
	return (EXIT_SUCCESS);
}
