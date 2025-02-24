/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:21:20 by shiori            #+#    #+#             */
/*   Updated: 2025/02/24 14:36:46 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK_TAKEN "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	int				eat_count;
	int				*ate_philos_num;
	bool			*must_stop;
	long			start_time;
	long			last_meal_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*stop_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*time_mutex;
}					t_philo;

typedef struct s_program
{
	pthread_t		monitor;
	int				num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	int				ate_philos_num;
	bool			must_stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	time_mutex;
	bool			stop_mutex_init;
	bool			eat_mutex_init;
	bool			time_mutex_init;
	bool			*forks_init;
	t_philo			*philos;
}					t_program;

// init.c
void				init_philos(t_program *program);
int					init_mutex(t_program *program);
void				init_program(t_program *program, char **argv);

// thread.c
int					thread_create(t_program *program);
int					thread_join(t_program *program);
int					must_stop_simulation(t_philo *philo);
void				print_status(t_philo *philo, char *status);
void				*philo_routine(void *arg);

// monitor.c
void				*monitor_routine(void *arg);

// philo_routine.c
void				thinking(t_philo *philo);
void				sleeping(t_philo *philo);
void				take_forks(t_philo *philo);
void				eating(t_philo *philo);
void				put_down_forks(t_philo *philo);

// utils.c
long				get_current_time(void);
int					ft_usleep(long milliseconds);
void				free_all_memory(t_program *program);

// libft.c
int					ft_strcmp(char *s1, char *s2);
int					ft_atoi(char *str);

#endif