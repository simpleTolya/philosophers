/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:19:51 by marmand           #+#    #+#             */
/*   Updated: 2022/01/08 19:06:38 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_clear_sems(t_utils *util)
{
	int	i;

	i = 0;
	while (i < util->philo_count)
	{
		sem_close(util->philos[i].eating_sem);
		i++;
	}
	sem_close(util->free_fork_count);
	sem_close(util->stdout_sem);
}

static int	ft_close_eating_sems(t_utils *util)
{
	int		i;
	char	name[18];

	ft_strcpy(name, "eating_sem_00_42\0");
	i = 0;
	while (i < util->philo_count)
	{
		sem_unlink(name);
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

void	ft_remove_sems(t_utils *util)
{
	ft_clear_sems(util);
	sem_unlink(FREE_FORK_COUNT_SEM_NAME);
	sem_unlink(STDOUT_SEM_NAME);
	ft_close_eating_sems(util);
}
