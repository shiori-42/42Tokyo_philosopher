/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:06:14 by shiori            #+#    #+#             */
/*   Updated: 2025/02/23 19:22:17 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_any_philosopher_death(t_philo *philos)
{
    long since_last_meal_time;
    int i = 0;

    while (i < philos[0].num_of_philos)
    {
        pthread_mutex_lock(philos[0].time_mutex);
        since_last_meal_time = get_current_time() - philos[i].last_meal_time;
        pthread_mutex_unlock(philos[0].time_mutex);
        
        if (since_last_meal_time >= philos[i].time_to_die)
        {
            pthread_mutex_lock(philos[0].stop_mutex);
            *philos[0].must_stop = true;
            pthread_mutex_unlock(philos[0].stop_mutex);
            print_status(&philos[i], DIED);
            return (1);
        }
        i++;
    }
    return (0);
}


int check_all_philosophers_ate(t_philo *philos)
{
    int i = 0;
    int ate_count = 0;

    if (philos[0].must_eat_count == -1)
        return (0);
    
    pthread_mutex_lock(philos[0].eat_mutex);
    while (i < philos[0].num_of_philos)
    {
        if (philos[i].eat_count == philos[i].must_eat_count)
            ate_count++;
        i++
    }
    pthread_mutex_unlock(philos[0].eat_mutex);

    if (ate_count == philos[0].num_of_philos)
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
        if (check_any_philosopher_death(philos))
            break; 
        if (check_all_philosophers_ate(philos))
            break; 
        ft_usleep(200);
    }
    // printf("monitor end\n");
    pthread_exit(NULL);
}



 
