/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:06:14 by shiori            #+#    #+#             */
/*   Updated: 2025/02/21 14:15:13 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_any_philosopher_death(t_philo *philos)
{
    long current_time;
    long since_last_meal_time;
    int is_dead;
    int i;

    
    i = 0;
    while (i < philos[0].num_of_philos)
    {
        pthread_mutex_lock(philos[i].time_mutex);
        current_time = get_current_time();
        since_last_meal_time = current_time - philos[i].last_meal_time;
        pthread_mutex_unlock(philos[i].time_mutex);
        is_dead = 0;
        if((since_last_meal_time >= philos[i].time_to_die))
            is_dead = 1;
        if (is_dead)
        {
            pthread_mutex_lock(philos[0].stop_mutex);
            *(philos[0].should_stop) = true;
            pthread_mutex_unlock(philos[0].stop_mutex);
            print_status(&philos[i], DIED);
            return (is_dead);
        }
        i++;
    }
    return (0);
}


int check_all_philosophers_satisfied(t_philo *philos)
{
    int i;
    int satisfied_count;
    
    satisfied_count = 0;
    if (philos[0].must_eat_count == -1)
        return (0);
    i = 0;
    while (i < philos[0].num_of_philos)
    {
        pthread_mutex_lock(philos[i].eat_mutex);
        if (philos[i].eat_count >= philos[i].must_eat_count)
            satisfied_count++;
        pthread_mutex_unlock(philos[i].eat_mutex);
        i++;
    }
    if (satisfied_count == philos[0].num_of_philos)
    {
        pthread_mutex_lock(philos[0].stop_mutex);
        *(philos[0].should_stop) = true;
        pthread_mutex_unlock(philos[0].stop_mutex);        
        return (1);
    }
    return (0);
}
   
void *monitor_routine(void *argv)
{
    t_philo *philos;

    philos = (t_philo *)argv;
    while (1)
    {
        if (check_any_philosopher_death(philos))
            break; 
        if (check_all_philosophers_satisfied(philos))
            break; 
    }
    return (NULL);
}

 
