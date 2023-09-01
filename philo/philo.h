/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:42:19 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/01 12:45:28 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define R "\x1b[1;31m"
# define G "\x1b[1;32m"
# define B "\x1b[1;36m"
# define Y "\x1b[1;33m"
# define M "\x1b[1;35m"
# define C "\x1b[0m"

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>

typedef struct data
{
	pthread_mutex_t	*forks;
	int				*last_meal;
	int				philo_count;
	pthread_mutex_t	state;
	int				current;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				must_eat;
}	t_data;

int	get_time(void);
pthread_mutex_t	*init_forks(int nb);
pthread_t	*init_philosopher(int nb, t_data data);
void	free_matrix(void **matrix, int size);
int	init_data(int ac, char **av, t_data *data);
void	*routine(t_data *arg);

#endif