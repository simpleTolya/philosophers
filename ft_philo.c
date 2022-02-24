/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:29:56 by marmand           #+#    #+#             */
/*   Updated: 2022/01/07 22:50:43 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philos_init(t_philo *philo, int philo_count,
	t_fork *forks, t_utils *util)
{
	int			i;
	pthread_t	ptid;

	i = 0;
	while (i < philo_count)
	{
		philo[i].philo_type = i + 1;
		philo[i].left = forks + i;
		philo[i].right = forks + ((i + 1) % util->philo_count);
		philo[i].stdout_mutex = &util->stdout_mutex;
		if (pthread_mutex_init(&philo[i].condition_mutex, 0))
			return (1);
		philo[i].eating_times = 0;
		philo[i].c_time_to_eat = util->time_to_eat;
		philo[i].c_time_to_sleep = util->time_to_sleep;
		philo[i].c_program_start_time = util->program_start_time;
		gettimeofday(&philo[i].last_time_eat, 0);
		if (pthread_create(&ptid, 0, ft_philo, &(philo[i])))
			return (1);
		pthread_detach(ptid);
		i++;
	}
	return (0);
}

int	ft_philo_sleep(t_philo *philo)
{
	ft_print(philo, SLEEPING);
	usleep(philo->c_time_to_sleep * 1000);
	return (0);
}

int	ft_philo_eat(t_philo *philo, int was_sleeping)
{
	t_fork	*min_fork;
	t_fork	*max_fork;

	min_fork = philo->right;
	max_fork = philo->left;
	if (philo->left->fork_type < philo->right->fork_type)
	{
		min_fork = philo->left;
		max_fork = philo->right;
	}
	ft_fork_lock(min_fork);
	ft_print(philo, TAKING_FORK);
	ft_fork_lock(max_fork);
	ft_print(philo, TAKING_FORK);
	ft_print(philo, EATING);
	usleep(philo->c_time_to_eat * 1000);
	pthread_mutex_lock(&philo->condition_mutex);
	philo->eating_times++;
	ft_update_last_time_eat(&philo->last_time_eat, philo, was_sleeping);
	pthread_mutex_unlock(&philo->condition_mutex);
	ft_fork_unlock(max_fork);
	ft_fork_unlock(min_fork);
	return (0);
}

int	ft_philo_think(t_philo *philo)
{
	ft_print(philo, THINKING);
	return (0);
}

int	ft_philo_was_died(t_philo *philo, t_utils *util)
{
	t_timeval	current_time;

	gettimeofday(&current_time, 0);
	pthread_mutex_lock(&philo->condition_mutex);
	if ((current_time.tv_sec - philo->last_time_eat.tv_sec) * 1000
		+ (current_time.tv_usec - philo->last_time_eat.tv_usec + 500) / 1000
		>= util->time_to_die)
	{
		pthread_mutex_unlock(&philo->condition_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->condition_mutex);
	return (0);
}
