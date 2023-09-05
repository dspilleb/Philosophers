/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:11:15 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/05 13:20:42 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(pthread_mutex_t *first_fork, \
pthread_mutex_t *second_fork, t_data *data, int nb)
{
	pthread_mutex_lock(first_fork);
	if (!data->state)
		unlock_forks_exit(first_fork, NULL);
	printf(M "%d %d has taken a fork\n" C, get_time(), nb);
	if (data->philo_count == 1)
	{
		printf(R "%d %d died\n" C, get_time(), nb);
		unlock_forks_exit(&data->forks[nb - 1], NULL);
	}
	pthread_mutex_lock(second_fork);
	if (!data->state)
		unlock_forks_exit(first_fork, second_fork);
	printf(M "%d %d has taken a fork\n" C, get_time(), nb);
}

void	eating(int nb, t_data *data)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = &data->forks[(nb - 1 + !(nb % 2)) % data->philo_count];
	second_fork = &data->forks[(nb - 1 + nb % 2) % data->philo_count];
	take_forks(first_fork, second_fork, data, nb);
	data->last_meal[nb - 1] = get_time();
	printf(B "%d %d is eating\n" C, get_time(), nb);
	my_sleep(data->time_to_eat);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

void	*routine(t_philo *philo)
{
	int	count;

	count = 0;
	while (philo->data->state && \
	(philo->data->must_eat == -1 || count < philo->data->must_eat))
	{
		eating(philo->number, philo->data);
		if (!philo->data->state)
			pthread_exit(EXIT_SUCCESS);
		printf(Y "%d %d is sleeping\n" C, get_time(), philo->number);
		if (!philo->data->state)
			pthread_exit(EXIT_SUCCESS);
		my_sleep(philo->data->time_to_sleep);
		if (!philo->data->state)
			pthread_exit(EXIT_SUCCESS);
		printf(G "%d %d is thinking\n" C, get_time(), philo->number);
		count++;
	}
	philo->pstate = FINISHED;
	pthread_exit(EXIT_SUCCESS);
}
