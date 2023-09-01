/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:42:23 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/01 11:03:27 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	time;
	static int		initial_time;

	gettimeofday(&time, NULL);
	if (!initial_time)
		initial_time = time.tv_usec;
	return (time.tv_usec - initial_time);
}

void	free_matrix(void **matrix, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(matrix[i]);
	free(matrix);
}

void	eating(int nb, t_data *data)
{
	pthread_mutex_lock(&data->forks[nb - 1]);
	printf(R "%d %d has taken a fork\n", get_time(), nb);
	pthread_mutex_lock(&data->forks[(nb + 1) % data->philo_count]);
	printf(R "%d %d has taken a fork\n", get_time(), nb);
	printf(B "%d %d is eating\n", nb, get_time());
	usleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks[nb - 1]);
	pthread_mutex_unlock(&data->forks[(nb + 1) % data->philo_count]);
}
void	*routine(t_data *arg)
{
	int count;
	int	my_id;

	my_id = arg->current;
	count = 0;
	while (arg->state == 1 && count != arg->must_eat)
	{
		eating(my_id, arg);
		printf(Y "%d %d  is sleeping\n", get_time(), my_id);
		usleep(arg->time_to_sleep);
		printf(G "%d %d is thinking\n", get_time(), my_id);
		count++;
	}
	pthread_exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_data data;

	if (ac == 5 || ac == 6)
	{
		init_data(ac, av, &data);
		data.forks = init_forks(atoi(av[1]));
		if (!data.forks)
			return(printf("ERROR MALLOC"), 0);
		if (!init_philosopher(atoi(av[1]), data))
			printf("malloc fail\n");
		//destroy mutex
	}
	else
		printf("gros argumente\n");
}
