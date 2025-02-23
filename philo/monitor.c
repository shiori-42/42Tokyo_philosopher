/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:06:14 by shiori            #+#    #+#             */
/*   Updated: 2025/02/23 23:04:19 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_any_philosopher_dead(t_philo *philos)
{
    int i;

    i = 0;
    while (i < philos[0].num_of_philos)
    {   
        long since_last_meal_time;
        
        pthread_mutex_lock(philos[i].time_mutex);
        since_last_meal_time=get_current_time() - philos[i].last_meal_time;
        pthread_mutex_unlock(philos[i].time_mutex);
        if (since_last_meal_time >= philos[i].time_to_die)
        {
            pthread_mutex_lock(philos[i].stop_mutex);
            *philos[i].must_stop = true;
            pthread_mutex_unlock(philos[i].stop_mutex);
            print_status(&philos[i], DIED);
            return (1);
        }
        i++;
    }
    return (0);
}

int check_all_philosophers_ate(t_philo *philos)
{
    int satisfied_philo;
    
     satisfied_philo=0;
    if (philos[0].must_eat_count == -1)
        return (0);
    
    pthread_mutex_lock(philos[0].eat_mutex);
    satisfied_philo=*(philos[0].ate_philos_num);
    pthread_mutex_unlock(philos[0].eat_mutex);
    if (satisfied_philo== philos[0].num_of_philos)
    {
        pthread_mutex_lock(philos[0].stop_mutex);
        *(philos[0].must_stop) = true;
        pthread_mutex_unlock(philos[0].stop_mutex);
        return (1);
    }
    return (0);
}

void *monitor_routine(void *argv)
{
    t_philo *philos = (t_philo *)argv;
    while (1)
    {
        if (check_any_philosopher_dead(philos))
            break; 
        if (check_all_philosophers_ate(philos))
            break; 
        ft_usleep(200);
    }
    pthread_exit(NULL);
}




 
