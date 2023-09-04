/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:42:23 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/04 19:02:09 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(useconds_t time)
{
	unsigned int start;

	start = get_time();
	while (get_time() < (start + time))
		usleep(1);
}

unsigned int	get_time(void)
{
	struct timeval			time;
	static struct timeval	initial_time;

	gettimeofday(&time, NULL);
	if (!initial_time.tv_sec)
	{
		initial_time.tv_sec = time.tv_sec;
		initial_time.tv_usec = time.tv_usec;
	}
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - 
		(initial_time.tv_sec * 1000 + initial_time.tv_usec / 1000));
}

int	is_dead(int nb, t_data *data)
{
	if ((get_time() - data->last_meal[nb - 1]) > data->time_to_die)
		return (1);
	return (0);
}

void	check_philos(t_data	*data)
{
	int	i;

	while (data->state)
	{
		i = -1;
		while (data->state && ++i < data->philo_count)
		{
			if (is_dead(i + 1, data) && data->philos[i].state == ALIVE)
			{
				printf(R "%d %d died\n", get_time(), i + 1);
				data->state = 0;
				pthread_exit(EXIT_SUCCESS);
			}
		}
	}
	pthread_exit(EXIT_SUCCESS);
}

void	free_matrix(void **matrix, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(matrix[i]);
	free(matrix);
}

void	destroy_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
	}
	free(data->forks);
}

void	unlock_forks_exit(void *fork1, void *fork2)
{
	if (fork1)
		pthread_mutex_unlock(fork1);
	if (fork2)
		pthread_mutex_unlock(fork2);
	pthread_exit(EXIT_SUCCESS);
}

void	eating_odd(int nb, t_data *data)
{
	pthread_mutex_lock(&data->forks[nb - 1].fork);
	if (!data->state)
		unlock_forks_exit(&data->forks[nb - 1].fork, NULL);
	printf(R "%d %d has taken a fork\n", get_time(), nb);
	if (data->philo_count == 1)
	{
		printf(R "%d %d died\n", get_time(), nb);
		unlock_forks_exit(&data->forks[nb - 1].fork, NULL);
	}
	pthread_mutex_lock(&data->forks[(nb) % data->philo_count].fork);
	if (!data->state)
		unlock_forks_exit(&data->forks[nb - 1].fork, &data->forks[(nb) % data->philo_count].fork);
	printf(R "%d %d has taken a fork\n", get_time(), nb);
	if (!data->state)
		unlock_forks_exit(&data->forks[nb - 1].fork, &data->forks[(nb) % data->philo_count].fork);
	data->last_meal[nb - 1] = get_time();
	printf(B "%d %d is eating\n", get_time(), nb);
	my_sleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks[nb - 1].fork);
	pthread_mutex_unlock(&data->forks[(nb) % data->philo_count].fork);
}

void eating_even(int nb, t_data *data)
{
	pthread_mutex_lock(&data->forks[(nb) % data->philo_count].fork);
	if (!data->state)
		unlock_forks_exit(&data->forks[(nb) % data->philo_count].fork, NULL);
	printf(R "%d %d has taken a fork\n", get_time(), nb);
	if (data->philo_count == 1)
	{
		printf(R "%d %d died\n", get_time(), nb);
		unlock_forks_exit(&data->forks[(nb) % data->philo_count].fork, NULL);
	}
	pthread_mutex_lock(&data->forks[nb - 1].fork);
	if (!data->state)
		unlock_forks_exit(&data->forks[(nb) % \
		data->philo_count].fork, &data->forks[nb - 1].fork);
	printf(R "%d %d has taken a fork\n", get_time(), nb);
	if (!data->state)
		unlock_forks_exit(&data->forks[(nb) % \
		data->philo_count].fork, &data->forks[nb - 1].fork);
	data->last_meal[nb - 1] = get_time();
	printf(B "%d %d is eating\n", get_time(), nb);
	my_sleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks[(nb) % data->philo_count].fork);
	pthread_mutex_unlock(&data->forks[nb - 1].fork);
}

void	*routine(t_philo *philo)
{
	int	count;

	count = 0;
	while (philo->data->state && (count < philo->data->must_eat || philo->data->must_eat == -1))
	{
		if (philo->number % 2 == 0)
			eating_even(philo->number, philo->data);
		else
			eating_odd(philo->number, philo->data);
		if (!philo->data->state)
			break ;
		printf(Y "%d %d  is sleeping\n", get_time(), philo->number);
		my_sleep(philo->data->time_to_sleep);
		if (!philo->data->state)
			break ;
		printf(G "%d %d is thinking\n", get_time(), philo->number);
		count++;
	}
	philo->state = FINISHED;
	pthread_exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (init_data(ac, av, &data))
			return (EXIT_FAILURE);
		data.forks = init_forks(atoi(av[1]));
		if (!data.forks)
			return(printf("ERROR MALLOC"), 0);
		init_philosopher(atoi(av[1]), &data); //check malloc fail
		destroy_forks(&data);
	}
	else
		printf("gros argumente\n");
}
