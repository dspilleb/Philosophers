/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:53:49 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/01 11:03:10 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(int nb)
{
	int				i;
	pthread_mutex_t	*forks;

	i = -1;
	if (nb <= 0)
		return (NULL);
	forks = malloc(sizeof(pthread_mutex_t) * nb);
	if (!forks)
		return (NULL);
	while (++i < nb)
		if (pthread_mutex_init(&forks[i], NULL))
			return (free_matrix((void **)forks, i), NULL);
	return (forks);
}

pthread_t	*init_philosopher(int nb, t_data data)
{
	int			i;
	pthread_t	*philos;

	if (nb <= 0)
		return (NULL);
	i = -1;
	philos = malloc(sizeof(pthread_t *) * nb);
	if (!philos)
		return (NULL);
	while (++i < nb)
	{
		if (pthread_create(&philos[i], NULL, (void *)routine, &data))
			return (free_matrix((void **)philos, i), NULL);
		usleep(10);
		data.current++;
	}
	i = -1;
	while (++i < nb)
		pthread_join(philos[i], NULL);
	return (philos);
}

void	init_data(int ac, char **av, t_data *data)
{
	data->current = 1;
	data->state = 1;
	data->philo_count = atoi(av[1]); //todo take my atoi
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		data->must_eat = atoi(av[5]);
	else
		data->must_eat = -1;
}