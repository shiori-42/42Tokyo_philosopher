/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:06:11 by shiori            #+#    #+#             */
/*   Updated: 2025/02/16 17:07:23 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void thinking(t_philo *philo)
{
    print_status(philo, THINKING);
}
void sleeping(t_philo *philo)
{
    print_status(philo, SLEEPING);
    ft_usleep(philo->time_to_sleep);
}

void take_forks(t_philo *philo)
{

    if (philo->num_of_philos == 1)
    {
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, FORK_TAKEN);
        ft_usleep(philo->time_to_die);
        pthread_mutex_unlock(philo->right_fork);
        return ;
    }
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
    print_status(philo, FORK_TAKEN);
    print_status(philo, FORK_TAKEN);
}

void eating(t_philo *philo)
{

    pthread_mutex_lock(philo->time_mutex);
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(philo->time_mutex);
    print_status(philo, EATING);
    ft_usleep(philo->time_to_eat);
    pthread_mutex_lock(philo->eat_mutex);
    philo->eat_count++;
    // printf("philo id %d:philo->eat_count: %d\n", philo->id,philo->eat_count);
    pthread_mutex_unlock(philo->eat_mutex);

}

void put_down_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}
