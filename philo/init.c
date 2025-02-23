// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   init.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/16 17:05:55 by shiori            #+#    #+#             */
// /*   Updated: 2025/02/16 18:21:49 by shiori           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "philo.h"

void	set_philo_input(t_program *program,t_philo *philo, char **argv, int i)
{
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->must_eat_count = ft_atoi(argv[5]);
	else
        philo->must_eat_count = -1;
    philo->id = i + 1;
    philo->eat_count = 0;
    philo->start_time = get_current_time();
    philo->last_meal_time = get_current_time();
    philo->must_stop = &program->must_stop;
    philo->stop_mutex = &program->stop_mutex;
    philo->eat_mutex = &program->eat_mutex;
    philo->time_mutex = &program->time_mutex;
    philo->left_fork = &program->forks[i];
    philo->right_fork = &program->forks[(i-1 + philo->num_of_philos) % philo->num_of_philos];
}

void	init_philos(t_program *program, char **argv)
{
	int	i;

	i = 0;
    while (i < program->num_of_philos)
	{
        set_philo_input(program,&program->philos[i], argv,i);
		i++;
	}
}

int init_mutex(t_program *program)
{
    int i;
    
    if (pthread_mutex_init(&program->stop_mutex, NULL) != 0)
        return (free_all_memory(program), 1);
    program->stop_mutex_init = true;

    if (pthread_mutex_init(&program->eat_mutex, NULL) != 0)
        return (free_all_memory(program), 1);
    program->eat_mutex_init = true;

    if (pthread_mutex_init(&program->time_mutex, NULL) != 0)
        return (free_all_memory(program), 1);
    program->time_mutex_init = true;

    program->forks = malloc(sizeof(pthread_mutex_t) * program->num_of_philos);
    program->forks_init = malloc(sizeof(bool) * program->num_of_philos);
    if (!program->forks || !program->forks_init)
        return (free_all_memory(program), 1);
    
    i = 0;
    while (i < program->num_of_philos)
    {
        program->forks_init[i] = false;
        if (pthread_mutex_init(&program->forks[i], NULL) != 0)
            return (free_all_memory(program), 1);
        program->forks_init[i] = true;
        i++;
    }
    return (0);
}

void init_program(t_program *program, char **argv)
{
    program->num_of_philos = ft_atoi(argv[1]);
    program->must_stop = false;
    program->philos = malloc(sizeof(t_philo) * program->num_of_philos);
    program->stop_mutex_init = false;
    program->eat_mutex_init = false;
    program->time_mutex_init = false;
}





