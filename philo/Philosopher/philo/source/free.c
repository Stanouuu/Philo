/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:43:19 by sbarrage          #+#    #+#             */
/*   Updated: 2023/03/20 14:39:50 by sbarrage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_errors_test(t_philo *philo, int i)
{
	while (i != 0)
	{
		i--;
		pthread_mutex_destroy(&(philo->to_free_2[i]));
	}
	free_errors_2(philo, 2);
	return (0);
}

int	free_errors_2(t_philo *philo, int i)
{
	if (i == 1)
		pthread_mutex_destroy(philo->wrt_prvlg);
	if (i == 2)
		pthread_mutex_destroy(philo->testing);
	if (philo->to_free)
		free(philo->to_free);
	if (philo->wrt_prvlg)
		free(philo->wrt_prvlg);
	if (philo->testing)
		free(philo->testing);
	if (philo->to_free_2)
		free(philo->to_free_2);
	return (0);
}

int	free_errors_fork(t_philo **philo, int i)
{
	int	j;

	j = 0;
	while (philo[j])
		j++;
	free_errors_test((*philo), j);
	while (i != 0)
	{
		i--;
		pthread_mutex_destroy(&((*philo)->to_free[i]));
	}
	return (0);
}

int	free_error(t_philo **philo, int i)
{
	free((*philo)->alive);
	free((*philo)->first_time);
	while (i != 0)
	{
		i--;
		free(philo[i]);
	}
	return (0);
}

void	ft_free(t_philo **philo, int i)
{
	while (i != 0)
		pthread_join((philo[--i])->thread, NULL);
	while (philo[i] && i)
	{
		pthread_mutex_destroy((philo[i])->inditest);
		pthread_mutex_destroy((philo[i])->fork_right);
		i++;
	}
	pthread_mutex_destroy((philo[0])->testing);
	pthread_mutex_destroy(philo[0]->wrt_prvlg);
	free(philo[0]->testing);
	free(philo[0]->wrt_prvlg);
	free(philo[0]->to_free);
	free(philo[0]->to_free_2);
	free(philo[0]->alive);
	free(philo[0]->first_time);
	i = 0;
	while (philo[i])
		free(philo[i++]);
}
