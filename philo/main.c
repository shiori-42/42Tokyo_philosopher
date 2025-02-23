/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:06:04 by shiori            #+#    #+#             */
/*   Updated: 2025/02/24 01:38:05 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int validate_command_line_args(char **argv)
{
    if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 ||
        ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0 || ((argv[5] && ft_atoi(argv[5]) <= 0)))
        return (1);
    return (0);
}

int main(int argc, char **argv)
{
    t_program program;

    if (argc != 5 && argc != 6)
        return (write(2, "Error: Wrong argument count\n", 28), 1);
    if (validate_command_line_args(argv) == 1)
        return (write(2, "Error: Invalid argument\n", 24), 1);
    init_program(&program, argv);
    program.philos = malloc(sizeof(t_philo) * program.num_of_philos);
    if (!program.philos)
        return (write(2, "Error: Philosopher memory allocation failed\n", 42), 1);
    if(init_mutex(&program))
        return (write(2, "Error: Mutex initialization failed\n", 33), 1);
	init_philos(&program);
    if(thread_create(&program))
        return (write(2, "Error: Thread creation failed\n", 29), 1);
    if(thread_join(&program))
        return (write(2, "Error: Thread join failed\n", 25), 1);
    free_all_memory(&program);
    return (0);
}

