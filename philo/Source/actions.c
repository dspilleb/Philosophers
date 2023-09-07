/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:11:15 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/07 19:07:50 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(pthread_mutex_t *first_fork, \
pthread_mutex_t *second_fork, t_data *data, int nb)
{
	pthread_mutex_lock(first_fork);
	pthread_mutex_lock(&data->talk);
	if (!data->state)
		unlock_mutex_exit(&data->talk, first_fork, NULL);
	printf(M "%d %d has taken a fork\n" C, get_time(), nb);
	pthread_mutex_unlock(&data->talk);
	if (data->philo_count == 1)
	{
		printf(R "%d %d died\n" C, get_time(), nb);
		unlock_mutex_exit(NULL, &data->forks[nb - 1], NULL);
	}
	pthread_mutex_lock(second_fork);
	pthread_mutex_lock(&data->talk);
	if (!data->state)
		unlock_mutex_exit(&data->talk, first_fork, second_fork);
	printf(M "%d %d has taken a fork\n" C, get_time(), nb);
	pthread_mutex_unlock(&data->talk);
}

void	eating(int nb, t_data *data)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = &data->forks[(nb - 1 + !(nb % 2)) % data->philo_count];
	second_fork = &data->forks[(nb - 1 + nb % 2) % data->philo_count];
	take_forks(first_fork, second_fork, data, nb);
	data->last_meal[nb - 1] = get_time();
	pthread_mutex_lock(&data->talk);
	if (!data->state)
		unlock_mutex_exit(&data->talk, first_fork, second_fork);
	printf(B "%d %d is eating\n" C, get_time(), nb);
	pthread_mutex_unlock(&data->talk);
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
		pthread_mutex_lock(&philo->data->talk);
		if (!philo->data->state)
			unlock_mutex_exit(&philo->data->talk, NULL, NULL);
		printf(Y "%d %d is sleeping\n" C, get_time(), philo->number);
		pthread_mutex_unlock(&philo->data->talk);
		my_sleep(philo->data->time_to_sleep);
		pthread_mutex_lock(&philo->data->talk);
		if (!philo->data->state)
			unlock_mutex_exit(&philo->data->talk, NULL, NULL);
		printf(G "%d %d is thinking\n" C, get_time(), philo->number);
		pthread_mutex_unlock(&philo->data->talk);
		count++;
	}
	philo->pstate = FINISHED;
	pthread_exit(EXIT_SUCCESS);
}
