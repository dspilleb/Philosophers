/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:53:49 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/04 18:33:17 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*init_forks(int nb)
{
	int				i;
	t_fork			*forks;

	i = -1;
	if (nb <= 0)
		return (NULL);
	forks = malloc(sizeof(t_fork) * nb);
	if (!forks)
		return (NULL);
	while (++i < nb)
	{
		if (pthread_mutex_init(&forks[i].fork, NULL))
			return (free_matrix((void **)forks, i), NULL);
		forks[i].lock = 0;
	}
	return (forks);
}

void	 init_philosopher(int nb, t_data *data)
{
	int			i;
	pthread_t	monitoring;

	if (nb <= 0)
		return ;
	i = -1;
	data->philos = malloc(sizeof(t_philo) * nb);
	if (!data->philos)
		return ;
	pthread_create(&monitoring, NULL, (void *)check_philos, data);
	while (++i < nb)
	{
		data->philos[i].state = ALIVE;
		data->philos[i].number = i + 1;
		data->philos[i].data = data;
		if (pthread_create(&data->philos[i].philo, NULL, (void *)routine, (void *) &data->philos[i]))
			return (free_matrix((void **)data->philos, i));
	}
	i = -1;
	while (++i < nb)
		pthread_join(data->philos[i].philo, NULL);
	data->state = 0;
	pthread_join(monitoring, NULL);
}

int	init_data(int ac, char **av, t_data *data)
{
	int i;

	i = -1;
	data->current = 1;
	if (pthread_mutex_init(&data->lock, NULL))
		return (EXIT_FAILURE);
	data->philo_count = atoi(av[1]); //todo take my atoi
	data->time_to_die = atoi(av[2]);
	data->state = 1;
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		data->must_eat = atoi(av[5]);
	else
		data->must_eat = -1;
	data->last_meal = malloc (sizeof(int) * data->philo_count);
	if (!data->last_meal)
		return (EXIT_FAILURE);
	while (++i < data->philo_count)
		data->last_meal[i] = 0;
	return (EXIT_SUCCESS);
}
