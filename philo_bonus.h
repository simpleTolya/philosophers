/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:10:01 by marmand           #+#    #+#             */
/*   Updated: 2022/01/08 19:26:38 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>
# include <stdlib.h>

# define PHILO_MAX 1000
# define FREE_FORK_COUNT_SEM_NAME "ffc_sem42"
# define STDOUT_SEM_NAME "stdout_sem42"
# define EATING 1
# define THINKING 2
# define SLEEPING 3
# define TAKING_FORK 4
# define DYING 5

typedef struct timeval	t_timeval;

typedef struct s_philo
{
	sem_t		*eating_sem;
	pid_t		pid;
	t_timeval	last_eat_time;
	int			eating_times;
}	t_philo;

typedef struct s_utils
{
	sem_t		*free_fork_count;
	sem_t		*stdout_sem;
	t_philo		philos[PHILO_MAX];
	pthread_t	add_thread;
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			c_eating_times;
	t_timeval	program_start_time;
}	t_utils;

int		ft_init_argc(t_utils *util, int argc, char *argv[]);

char	*ft_strcpy(char *dst, const char *src);
int		ft_atoi(const char *str, int *_res);
int		ft_print(t_utils *util, int philo_num, int condition);

void	*eating_observe(void *data);
int		ft_run_philo(t_utils *util, int philo_num);
void	ft_clear_sems(t_utils *util);
void	ft_remove_sems(t_utils *util);

#endif