/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:19:57 by marmand           #+#    #+#             */
/*   Updated: 2022/01/08 19:26:17 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str, int *_res)
{
	long long	res;
	int			sign;

	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += (*str - '0');
		str++;
	}
	if (*str != 0)
		return (1);
	*_res = (res * sign);
	return (0);
}

long	ft_get_current_time(t_utils *util)
{
	t_timeval	tm;

	gettimeofday(&tm, 0);
	return ((tm.tv_sec - util->program_start_time.tv_sec) * 1000
		+ (tm.tv_usec - util->program_start_time.tv_usec) / 1000);
}

int	ft_print(t_utils *util, int philo_num, int condition)
{
	sem_wait(util->stdout_sem);
	if (condition == EATING)
		printf("%ld %d is eating\n",
			ft_get_current_time(util), philo_num);
	else if (condition == SLEEPING)
		printf("%ld %d is sleeping\n",
			ft_get_current_time(util), philo_num);
	else if (condition == THINKING)
		printf("%ld %d is thinking\n",
			ft_get_current_time(util), philo_num);
	else if (condition == TAKING_FORK)
		printf("%ld %d has taken a fork\n",
			ft_get_current_time(util), philo_num);
	else if (condition == DYING)
	{
		printf("%ld %d died\n",
			ft_get_current_time(util), philo_num);
		return (0);
	}
	sem_post(util->stdout_sem);
	return (0);
}

char	*ft_strcpy(char *dst, const char *src)
{
	char	*res;

	res = dst;
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	return (res);
}
