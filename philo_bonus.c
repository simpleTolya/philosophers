/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:20:03 by marmand           #+#    #+#             */
/*   Updated: 2022/01/08 21:04:22 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_wait_and_kill(t_utils *util, pid_t observer_pid)
{
	pid_t	died_philo_pid;
	int		i;

	died_philo_pid = waitpid(-1, 0, 0);
	if (observer_pid)
		kill(observer_pid, SIGKILL);
	i = 0;
	while (i < util->philo_count)
	{
		if (util->philos[i].pid != died_philo_pid)
			kill(util->philos[i].pid, SIGKILL);
		i++;
	}
}

static int	ft_is_all_eat_more(t_philo *philos,
	int philo_count, int eating_times)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		if (philos[i].eating_times < eating_times)
			return (0);
		i++;
	}
	return (1);
}

static void	ft_kill_all(t_utils *util)
{
	int	i;

	i = 0;
	while (i < util->philo_count)
	{
		kill(util->philos[i].pid, SIGKILL);
		i++;
	}
}

void	*eating_observe(void *data)
{
	t_utils	*util;
	int		i;

	util = data;
	while (1)
	{
		i = 0;
		while (i < util->philo_count)
		{
			sem_wait(util->philos[i].eating_sem);
			util->philos[i].eating_times++;
			if (ft_is_all_eat_more(util->philos,
					util->philo_count, util->c_eating_times))
			{
				ft_kill_all(util);
				exit(0);
			}
			i++;
		}
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_utils	util;
	int		i;
	pid_t	observer_pid;

	if (ft_init_argc(&util, argc, argv))
		return (1);
	i = 0;
	while (i < util.philo_count)
	{
		util.philos[i].pid = fork();
		if (util.philos[i].pid == 0)
			return (ft_run_philo(&util, i));
		i++;
	}
	observer_pid = 0;
	if (util.c_eating_times != -1)
	{
		observer_pid = fork();
		if (observer_pid == 0)
			eating_observe(&util);
	}
	ft_wait_and_kill(&util, observer_pid);
	ft_remove_sems(&util);
	return (0);
}
