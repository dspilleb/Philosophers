/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:42:23 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/04 13:55:43 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
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
		while (++i < data->philo_count)
		{
			if (is_dead(i + 1, data) && data->philos[i].state == ALIVE)
			{
				data->state = 0;
				printf(R "%d %d died\n", get_time(), i + 1);
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
		if (data->forks[i].lock)
			pthread_mutex_unlock(&data->forks[i].fork);
		pthread_mutex_destroy(&data->forks[i].fork);
	}
	free(data->forks);
}

void	eating(int nb, t_data *data)
{
	pthread_mutex_lock(&data->forks[nb - 1].fork);
	data->forks[nb - 1].lock = 1;
	if (!data->state)
		pthread_exit(EXIT_SUCCESS);
	printf(R "%d %d has taken a fork\n", get_time(), nb);
	if (data->philo_count == 1)
		pthread_exit(EXIT_SUCCESS);
	pthread_mutex_lock(&data->forks[(nb) % data->philo_count].fork);
	data->forks[(nb) % data->philo_count].lock = 1;
	if (!data->state)
		pthread_exit(EXIT_SUCCESS);
	printf(R "%d %d has taken a fork\n", get_time(), nb);
	if (!data->state)
		pthread_exit(EXIT_SUCCESS);
	printf(B "%d %d is eating\n", get_time(), nb);
	data->last_meal[nb - 1] = get_time();
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[nb - 1].fork);
	data->forks[nb - 1].lock = 0;
	pthread_mutex_unlock(&data->forks[(nb) % data->philo_count].fork);
	data->forks[(nb) % data->philo_count].lock = 0;
}

void	*routine(t_data *arg)
{
	int	count;
	int	my_id;

	my_id = arg->current;
	count = 0;
	while (arg->state && (count < arg->must_eat || arg->must_eat == -1))
	{
		eating(my_id, arg);
		if (!arg->state)
			break ;
		printf(Y "%d %d  is sleeping\n", get_time(), my_id);
		usleep(arg->time_to_sleep * 1000);
		if (!arg->state)
			break ;
		printf(G "%d %d is thinking\n", get_time(), my_id);
		count++;
	}
	arg->philos[my_id - 1].state = FINISHED;
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
