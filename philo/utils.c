/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:10:04 by shiori            #+#    #+#             */
/*   Updated: 2025/02/24 14:28:52 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(long milliseconds)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(100);
	return (0);
}

static void	destroy_basic_mutexes(t_program *program)
{
	if (program->stop_mutex_init)
		pthread_mutex_destroy(&program->stop_mutex);
	if (program->eat_mutex_init)
		pthread_mutex_destroy(&program->eat_mutex);
	if (program->time_mutex_init)
		pthread_mutex_destroy(&program->time_mutex);
}

void	free_all_memory(t_program *program)
{
	int	i;

	destroy_basic_mutexes(program);
	if (program->forks && program->forks_init)
	{
		i = 0;
		while (i < program->num_of_philos)
		{
			if (program->forks_init[i])
				pthread_mutex_destroy(&program->forks[i]);
			i++;
		}
		free(program->forks_init);
	}
	if (program->forks)
		free(program->forks);
	if (program->philos)
		free(program->philos);
}
