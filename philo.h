/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:35:46 by marmand           #+#    #+#             */
/*   Updated: 2022/01/08 19:13:29 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# define PHILO_MAX 200
# define EATING 1
# define THINKING 2
# define SLEEPING 3
# define TAKING_FORK 4
# define DYING 5

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef struct s_fork
{
	int		fork_type;
	int		is_busy;
	t_mutex	mutex;
}	t_fork;

typedef struct s_philo
{
	int			philo_type;
	t_fork		*left;
	t_fork		*right;
	t_mutex		*stdout_mutex;
	t_mutex		condition_mutex;
	int			eating_times;
	t_timeval	last_time_eat;
	long int	c_time_to_eat;
	long int	c_time_to_sleep;
	t_timeval	c_program_start_time;
}	t_philo;

typedef struct s_utils
{
	int			i;
	int			eating_times_gt;
	int			time_to_eat;
	int			time_to_die;
	int			time_to_sleep;
	int			eating_times;
	int			philo_count;
	t_mutex		stdout_mutex;
	t_timeval	program_start_time;
}	t_utils;

int		ft_atoi(const char *str, int *_res);
int		ft_init_argc(t_utils *util, int argc, char *argv[]);
int		ft_print(t_philo *philo, int condition);
void	ft_update_last_time_eat(t_timeval *tv, t_philo *philo, int first);
void	*ft_philo(void *data);

int		ft_forks_init(t_fork *forks, int forks_count);
int		ft_fork_lock(t_fork *fork);
int		ft_fork_unlock(t_fork *fork);
int		ft_forks_destroy(t_fork *forks, int forks_count);

int		ft_philos_init(t_philo *philo, int philo_count,
			t_fork	*forks, t_utils *util);
int		ft_philo_sleep(t_philo *philo);
int		ft_philo_eat(t_philo *philo, int was_sleeping);
int		ft_philo_think(t_philo *philo);
int		ft_philo_was_died(t_philo *philo, t_utils *util);

#endif