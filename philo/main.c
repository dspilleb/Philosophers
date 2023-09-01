/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:42:23 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/01 18:27:46 by dspilleb         ###   ########.fr       */
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
	//printf(B "%d %d im waiting to EAT OPEN TGHE YNOOR\n", nb, get_time()); //DEBUG
	pthread_mutex_lock(&data->forks[nb - 1]);
	printf(R "%d %d has taken a fork\n", get_time(), nb);
	pthread_mutex_lock(&data->forks[(nb + 1) % data->philo_count]);
	printf(R "%d %d has taken a fork\n", get_time(), nb);
	printf(B "%d %d is eating\n", get_time(), nb);
	data->last_meal[nb - 1] = get_time();
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[nb - 1]);
	pthread_mutex_unlock(&data->forks[(nb + 1) % data->philo_count]);
}

void	*routine(t_data *arg)
{
	int	count;
	int	my_id;

	my_id = arg->current;
	count = 0;
	printf(M "%d %d I HAVE BEEN SUMMONED\n", get_time(), my_id);
	while (count < arg->must_eat || arg->must_eat == -1)
	{
		if (get_time() - arg->last_meal[my_id - 1] >= arg->time_to_die)
		{
			printf(R "%d %d died\n", get_time(), my_id);
			exit(0);
		}
		eating(my_id, arg);
		printf(Y "%d %d  is sleeping\n", get_time(), my_id);
		usleep(arg->time_to_sleep * 1000);
		printf(G "%d %d is thinking\n", get_time(), my_id);
		count++;
	}
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
		if (!init_philosopher(atoi(av[1]), data))
			printf("malloc fail\n");
		//destroy mutex
	}
	else
		printf("gros argumente\n");
}
