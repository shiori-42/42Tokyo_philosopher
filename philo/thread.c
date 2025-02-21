/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:31:05 by shiori            #+#    #+#             */
/*   Updated: 2025/02/21 13:35:34 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	thread_create(t_program *program)
{
    pthread_t	monitor;
	int			i;
    
	i = 0;
	while (i < program->num_of_philos)
	{
        pthread_create(&program->philos[i].thread, NULL,philo_routine,
            &program->philos[i]);
            i++;
        }
    pthread_create(&monitor, NULL,monitor_routine, program->philos);
    i = 0;
	while (i < program->num_of_philos)
	{
        pthread_join(program->philos[i].thread,NULL);
		i++;
	}
    pthread_join(monitor,NULL);
}

int should_stop_simulation(t_philo *philo)
{
    int should_stop;

    pthread_mutex_lock(philo->stop_mutex);
    should_stop = *philo->should_stop;
    pthread_mutex_unlock(philo->stop_mutex);
    return should_stop;
}


void print_status(t_philo *philo,const char *status)
{
    if (!should_stop_simulation(philo))
    {
        pthread_mutex_lock(philo->print_mutex);
        printf("%ld %d %s\n", get_current_time() - philo->start_time, philo->id, status);
        pthread_mutex_unlock(philo->print_mutex);
    }
    else if (strcmp(status, DIED) == 0) 
    {
        pthread_mutex_lock(philo->print_mutex);
        printf("%ld %d %s\n", get_current_time() - philo->start_time, philo->id, status);
        pthread_mutex_unlock(philo->print_mutex);
    }
}

void *philo_routine(void *argv)
{
    t_philo *philo;
    
    philo= (t_philo *)argv;
    if (philo->id % 2 == 0)
        ft_usleep(1);
    while (!should_stop_simulation(philo))
    {
        take_forks(philo);
        eating(philo);
        put_down_forks(philo);
        sleeping(philo);
        thinking(philo);
    }
    pthread_exit(NULL);
}