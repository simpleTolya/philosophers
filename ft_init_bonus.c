/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:20:00 by marmand           #+#    #+#             */
/*   Updated: 2022/01/08 20:01:52 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_init_sems(t_utils *util)
{
	util->free_fork_count = sem_open(FREE_FORK_COUNT_SEM_NAME, O_CREAT,
			S_IRWXU, util->philo_count);
	if (util->free_fork_count == SEM_FAILED)
		return (-1);
	util->stdout_sem = sem_open(STDOUT_SEM_NAME, O_CREAT,
			S_IRWXU, 1);
	if (util->stdout_sem == SEM_FAILED)
		return (-1);
	return (0);
}

static int	ft_init_eating_sems(t_utils *util)
{
	int		i;
	char	name[18];

	ft_strcpy(name, "eating_sem_00_42\0");
	i = 0;
	while (i < util->philo_count)
	{
		util->philos[i].eating_times = 0;
		util->philos[i].eating_sem = sem_open(name, O_CREAT,
				S_IRWXU, 0);
		if (util->philos[i].eating_sem == SEM_FAILED)
			return (1);
		if (name[12] == '9')
		{
			if (name[11] == '9')
				return (1);
			name[12] = '0';
			name[11]++;
		}
		else
			name[12]++;
		i++;
	}
	return (0);
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
		util->c_eating_times = -1;
		gettimeofday(&util->program_start_time, 0);
		if (ft_init_eating_sems(util))
			return (1);
		if (ft_init_sems(util))
			return (1);
		if (argc == 6)
			return (ft_atoi(argv[5], &util->c_eating_times));
		return (0);
	}
	return (1);
}
