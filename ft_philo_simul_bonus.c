/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_simul_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:11:16 by marmand           #+#    #+#             */
/*   Updated: 2022/01/08 21:01:02 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philo_observe(void *data)
{
	t_timeval	current_time;
	t_utils		*util;

	util = data;
	while (1)
	{
		gettimeofday(&current_time, 0);
		if ((current_time.tv_sec
				- util->philos[util->philo_count].last_eat_time.tv_sec) * 1000
			+ (current_time.tv_usec
				- util->philos[util->philo_count].last_eat_time.tv_usec) / 1000
			>= util->time_to_die)
		{
			ft_print(util, util->philo_count, DYING);
			exit(1);
		}
		usleep(500);
	}
}

int	ft_run_philo(t_utils *util, int philo_num)
{
	util->philo_count = philo_num;
	gettimeofday(&util->philos[philo_num].last_eat_time, 0);
	pthread_create(&util->add_thread, 0, philo_observe, util);
	pthread_detach(util->add_thread);
	while (1)
	{
		sem_wait(util->free_fork_count);
		ft_print(util, philo_num, TAKING_FORK);
		sem_wait(util->free_fork_count);
		ft_print(util, philo_num, TAKING_FORK);
		ft_print(util, philo_num, EATING);
		sem_post(util->philos[philo_num].eating_sem);
		usleep(util->time_to_eat * 1000);
		gettimeofday(&util->philos[philo_num].last_eat_time, 0);
		sem_post(util->free_fork_count);
		sem_post(util->free_fork_count);
		ft_print(util, philo_num, SLEEPING);
		usleep(util->time_to_sleep * 1000);
		ft_print(util, philo_num, THINKING);
	}
}
