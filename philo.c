/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:55:29 by marmand           #+#    #+#             */
/*   Updated: 2022/01/08 19:12:48 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *data)
{
	if (((t_philo *)data)->philo_type % 2 == 0)
		usleep(2500);
	ft_philo_eat((t_philo *) data, 0);
	ft_philo_sleep((t_philo *) data);
	ft_philo_think((t_philo *) data);
	while (1)
	{
		ft_philo_eat((t_philo *) data, 1);
		ft_philo_sleep((t_philo *) data);
		ft_philo_think((t_philo *) data);
	}
	return (0);
}

int	ft_simulate(t_fork *forks, t_philo *philos, t_utils *util)
{
	while (1)
	{
		util->i = 0;
		util->eating_times_gt = 1;
		while (util->i < util->philo_count)
		{
			if (util->eating_times == -1
				|| philos[util->i].eating_times < util->eating_times)
				util->eating_times_gt = 0;
			if (ft_philo_was_died(&philos[util->i], util))
			{
				ft_print(&philos[util->i], DYING);
				ft_forks_destroy(forks, util->philo_count);
				pthread_mutex_destroy(&util->stdout_mutex);
				return (1);
			}
			++util->i;
		}
		if (util->eating_times_gt)
		{
			ft_forks_destroy(forks, util->philo_count);
			pthread_mutex_destroy(&util->stdout_mutex);
			return (0);
		}
	}
}

int	ft_init_argc(t_utils *util, int argc, char *argv[])
{
	if (argc >= 5 && argc <= 6)
	{
		if (ft_atoi(argv[1], &util->philo_count))
			return (1);
		if (ft_atoi(argv[2], &util->time_to_die))
			return (1);
		if (ft_atoi(argv[3], &util->time_to_eat))
			return (1);
		if (ft_atoi(argv[4], &util->time_to_sleep))
			return (1);
		util->eating_times = -1;
		if (pthread_mutex_init(&util->stdout_mutex, 0))
			return (1);
		gettimeofday(&util->program_start_time, 0);
	}
	else
		return (-1);
	if (argc == 6)
	{
		if (ft_atoi(argv[5], &util->eating_times))
			return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_fork	forks[PHILO_MAX];
	t_philo	philos[PHILO_MAX];
	t_utils	util;

	if (ft_init_argc(&util, argc, argv))
		return (1);
	if (ft_forks_init(forks, util.philo_count))
		return (1);
	if (ft_philos_init(philos, util.philo_count, forks, &util))
		return (1);
	return (ft_simulate(forks, philos, &util));
	return (0);
}
