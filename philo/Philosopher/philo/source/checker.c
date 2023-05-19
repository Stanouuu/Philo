/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:48:38 by sbarrage          #+#    #+#             */
/*   Updated: 2023/03/20 14:41:29 by sbarrage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_test(t_philo *philo)
{
	if (*(philo->alive) == 0)
	{
		pthread_mutex_unlock(philo->testing);
		return (0);
	}
	return (1);
}

void	order_66(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		pthread_mutex_lock(philos[i]->testing);
		*(philos[i]->alive) = 0;
		pthread_mutex_unlock(philos[i]->testing);
		i++;
	}
}

int	starved(t_philo **philos, int n, int i)
{
	pthread_mutex_unlock(philos[i]->testing);
	order_66(philos);
	pthread_mutex_lock(philos[i]->wrt_prvlg);
	ft_printf("%d %d died\n", n, philos[i]->nbr);
	pthread_mutex_unlock(philos[i]->wrt_prvlg);
	return (0);
}

int	ft_check_ate(t_philo **philos)
{
	int				i;
	int				n;
	int				a;
	struct timeval	current;

	i = 0;
	n = 0;
	while (philos[i])
	{
		gettimeofday(&current, NULL);
		pthread_mutex_lock(philos[i]->testing);
		a = (current.tv_usec + (current.tv_sec % 1000) * 1000000);
		n = (a - *philos[i]->first_time) / 1000;
		if ((n - philos[i]->last_meal) > (philos[i]->die))
			return (starved(philos, n, i));
		pthread_mutex_unlock(philos[i++]->testing);
		usleep(100);
	}
	return (1);
}

void	ft_checker(t_philo **checker)
{
	pthread_mutex_unlock(checker[0]->testing);
	pthread_mutex_lock(checker[0]->inditest);
	usleep((checker[0]->die * 1000) / 4);
	pthread_mutex_unlock(checker[0]->inditest);
	while (ft_check_ate(checker) != 0)
	{
	}
}
