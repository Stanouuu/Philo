/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:50:02 by sbarrage          #+#    #+#             */
/*   Updated: 2023/03/20 14:47:34 by sbarrage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat_rgt(t_philo *philo)
{
	ft_print_action(philo, "is thinking\n", 0);
	pthread_mutex_lock(philo->fork_right);
	if (ft_print_action(philo, "has taken a fork\n", 0) == 0)
	{
		pthread_mutex_unlock(philo->fork_right);
		return (0);
	}
	if (!philo->fork_left)
	{
		pthread_mutex_unlock(philo->fork_right);
		return (0);
	}
	pthread_mutex_lock(philo->fork_left);
	if (ft_print_action(philo, "has taken a fork\n", 0) == 0)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (0);
	}
	if (ft_print_action(philo, "is eating\n", 1) == 1)
		usleep(philo->eat * 1000);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (1);
}

int	ft_eat_lft(t_philo *philo)
{
	ft_print_action(philo, "is thinking\n", 0);
	if (philo->total % 2 == 1)
		usleep((philo->eat - philo->sleep) * 1000);
	if (philo->last_meal == 0)
		usleep(philo->eat * 500);
	pthread_mutex_lock(philo->fork_left);
	if (ft_print_action(philo, "has taken a fork\n", 0) == 0)
	{
		pthread_mutex_unlock(philo->fork_left);
		return (0);
	}
	pthread_mutex_lock(philo->fork_right);
	if (ft_print_action(philo, "has taken a fork\n", 0) == 0)
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return (0);
	}
	if (ft_print_action(philo, "is eating\n", 1) == 1)
		usleep(philo->eat * 1000);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	return (1);
}

int	ft_alive(t_philo *philo)
{
	if (philo->nbr % 2 == 1)
	{
		if (ft_eat_rgt(philo) == 0)
			return (0);
	}
	else
	{
		if (ft_eat_lft(philo) == 0)
			return (0);
	}
	if (ft_print_action(philo, "is sleeping\n", 0) == 0)
		return (0);
	usleep(philo->sleep * 1000);
	return (1);
}

void	*ft_philo(void *voi)
{
	t_philo			*philo;
	struct timeval	first_time;
	int				n;

	philo = (t_philo *) voi;
	pthread_mutex_lock(philo->testing);
	if (philo->nbr == 1)
	{
		gettimeofday(&first_time, NULL);
		n = (first_time.tv_sec % 1000) * 1000000;
		*(philo->first_time) = first_time.tv_usec + n;
	}
	pthread_mutex_unlock(philo->testing);
	while (*philo->first_time == -1)
	{
	}
	while (ft_alive(philo))
	{
	}
	return (NULL);
}
