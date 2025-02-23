/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:10:04 by shiori            #+#    #+#             */
/*   Updated: 2025/02/23 03:03:11 by shiori           ###   ########.fr       */
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
		usleep(500);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((s1[i] != s2[i] || !s1[i] || !s2[i]))
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}


void free_all_memory(t_program *program)
{
    int i;

    if (program->stop_mutex_init)
        pthread_mutex_destroy(&program->stop_mutex);
    if (program->eat_mutex_init)
        pthread_mutex_destroy(&program->eat_mutex);
    if (program->time_mutex_init)
        pthread_mutex_destroy(&program->time_mutex);

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

int ft_atoi(char *str)
{
    int i=0;
    int sign=1;
    int result=0;
  
    if(str[i]=='-' || str[i]=='+')
    {
        if(str[i]=='-')
            sign=-1;
        i++;
    }
    while(str[i]>='0' && str[i]<='9')
    {
        result=result*10+(str[i]-'0');
        i++;
    } 
    return (sign*result);
}
