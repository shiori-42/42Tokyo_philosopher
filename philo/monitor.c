/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:06:14 by shiori            #+#    #+#             */
/*   Updated: 2025/02/24 01:40:23 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool check_any_philosopher_dead(t_program *program)
{
    int i;
    t_philo *philos;

    i = 0;
    philos=program->philos;
    while (i < program->num_of_philos)
    {   
        long since_last_meal_time;
        
        pthread_mutex_lock(&program->time_mutex);
        since_last_meal_time=get_current_time() - philos[i].last_meal_time;
        pthread_mutex_unlock(&program->time_mutex);
        if (since_last_meal_time >= philos[i].time_to_die)
        {
            pthread_mutex_lock(philos[i].stop_mutex);
            *philos[i].must_stop = true;
            print_status(&philos[i], DIED);
            pthread_mutex_unlock(philos[i].stop_mutex);
            return (true);
        }
        i++;
    }
    return (false);
}

bool check_all_philosophers_ate(t_program *program)
{
    int satisfied_philo;
    
    satisfied_philo=0;
    if (program->must_eat_count == -1)
        return (0);
    
    pthread_mutex_lock(&program->eat_mutex);
    satisfied_philo=program->ate_philos_num;
    pthread_mutex_unlock(&program->eat_mutex);
    if (satisfied_philo== program->num_of_philos)
    {
        pthread_mutex_lock(&program->stop_mutex);
        program->must_stop = true;
        pthread_mutex_unlock(&program->stop_mutex);
        return (true);
    }
    return (false);
}

void *monitor_routine(void *argv)
{
    t_program *program = (t_program *)argv;
    while (1)
    {
        if (check_any_philosopher_dead(program))
            break; 
        if (check_all_philosophers_ate(program))
            break; 
        ft_usleep(60);
    }
    pthread_exit(NULL);
}




 
