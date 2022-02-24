/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:40:02 by marmand           #+#    #+#             */
/*   Updated: 2022/01/08 19:12:39 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long	ft_get_current_time(t_philo *philo)
{
	t_timeval	tm;

	gettimeofday(&tm, 0);
	return ((tm.tv_sec - philo->c_program_start_time.tv_sec) * 1000
		+ (tm.tv_usec - philo->c_program_start_time.tv_usec) / 1000);
}

int	ft_print(t_philo *philo, int condition)
{
	pthread_mutex_lock(philo->stdout_mutex);
	if (condition == EATING)
		printf("%ld %d is eating\n",
			ft_get_current_time(philo), philo->philo_type);
	else if (condition == SLEEPING)
		printf("%ld %d is sleeping\n",
			ft_get_current_time(philo), philo->philo_type);
	else if (condition == THINKING)
		printf("%ld %d is thinking\n",
			ft_get_current_time(philo), philo->philo_type);
	else if (condition == TAKING_FORK)
		printf("%ld %d has taken a fork\n",
			ft_get_current_time(philo), philo->philo_type);
	else if (condition == DYING)
	{
		printf("%ld %d died\n",
			ft_get_current_time(philo), philo->philo_type);
		return (0);
	}
	pthread_mutex_unlock(philo->stdout_mutex);
	return (0);
}

void	ft_update_last_time_eat(t_timeval *tv, t_philo *philo, int was_sleeping)
{
	tv->tv_usec += philo->c_time_to_eat * 1000;
	if (tv->tv_usec >= 100000)
	{
		tv->tv_sec++;
		tv->tv_usec -= 100000;
	}
	if (was_sleeping)
	{
		tv->tv_usec += philo->c_time_to_sleep;
		if (tv->tv_usec >= 100000)
		{
			tv->tv_sec++;
			tv->tv_usec -= 100000;
		}
	}
}
