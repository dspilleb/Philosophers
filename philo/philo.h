/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:42:19 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/11 12:10:38 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ALIVE 1
# define FINISHED 0

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
# include <errno.h>

typedef struct fork_mutex
{
	pthread_mutex_t	fork;
}	t_fork;

typedef struct philosopher
{
	pthread_t		philo;
	int				pstate;
	int				number;
	struct data		*data;
}	t_philo;

typedef struct data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	talk;
	unsigned int	*last_meal;
	int				philo_count;
	int				state;
	unsigned int	time_to_sleep;
	unsigned int	time_to_eat;
	unsigned int	time_to_die;
	int				must_eat;
}	t_data;

void			check_philos(t_data	*data);
void			unlock_mutex_exit(void *talk, void *fork1, void *fork2);

//inits.c
int				init_forks(t_data *data);
int				init_philosophers(t_data *data);
int				init_data(int ac, char **av, t_data *data);

//routine.c
void			*routine(t_philo *philo);

//utils.c
void			free_matrix(void **matrix, int size);
unsigned int	get_time(void);
int				is_dead(int nb, t_data *data);
void			my_sleep(unsigned int time);

//parsing.c
int				ft_atoi(const char *nptr);
int				is_unsigned_int(char **av);

#endif