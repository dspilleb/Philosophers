/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:11:12 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/05 16:20:56 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	my_sleep(int time)
{
	int	start;

	start = get_time();
	while (get_time() < (start + time))
		usleep(500);
}

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
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - 
		((initial_time.tv_sec * 1000) + (initial_time.tv_usec / 1000)));
}

int	is_dead(int nb, t_data *data)
{
	if ((get_time() - data->last_meal[nb]) > data->time_to_die)
		return (1);
	return (0);
}
