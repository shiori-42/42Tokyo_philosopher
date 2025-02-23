/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:31:05 by shiori            #+#    #+#             */
/*   Updated: 2025/02/23 22:43:37 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int thread_create(t_program *program)
{

    int i = 0;

    if(pthread_create(&program->monitor, NULL, monitor_routine, program->philos)!=0)
    {
        free_all_memory(program);
        return(write(2, "Error: Failed to create monitor thread\n", 39), 1);
    }

    while (i < program->num_of_philos)
    {
        if(pthread_create(&program->philos[i].thread, NULL, philo_routine, &program->philos[i])!=0)
        {
            free_all_memory(program);
            return(write(2, "Error: Failed to create philosopher thread\n", 42), 1);
        }
        i++;
    }
    return (0);
}

int thread_join(t_program *program) 
{

    int i;
    
    i = 0;
    if(pthread_join(program->monitor, NULL)!=0)
    {
        free_all_memory(program);
        return(write(2, "Error: Failed to join monitor thread\n", 36), 1);
    }
    while (i < program->num_of_philos)
    {
        if(pthread_join(program->philos[i].thread, NULL)!=0)
        {
            free_all_memory(program);
            return(write(2, "Error: Failed to join philosopher thread\n", 40), 1);
        }
        i++;
    }
    return (0);

}

int must_stop_simulation(t_philo *philo)
{
    int is_must_stop;

    pthread_mutex_lock(philo->stop_mutex);
    is_must_stop = *philo->must_stop;
    pthread_mutex_unlock(philo->stop_mutex);
    return is_must_stop;
}

void print_status(t_philo *philo,char *status)
{
    pthread_mutex_lock(philo->stop_mutex);
    if ((ft_strcmp(status, DIED) == 0)|| !*philo->must_stop)
        printf("%ld %d %s\n", get_current_time() - philo->start_time, philo->id, status);
    pthread_mutex_unlock(philo->stop_mutex);
}

void *philo_routine(void *argv)
{
    t_philo *philo = (t_philo *)argv;
    if(philo->id % 2 == 0)
        ft_usleep(1);
    while (!must_stop_simulation(philo))
    {
 
        take_forks(philo);
        if (philo->num_of_philos == 1)
            return NULL;
        eating(philo);
        put_down_forks(philo);
        sleeping(philo);
        thinking(philo);
    }
    // printf("%d exit\n",philo->id);
    return NULL;
}



