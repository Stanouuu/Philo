/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:46:03 by sbarrage          #+#    #+#             */
/*   Updated: 2023/03/20 15:46:13 by sbarrage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_lft_fork_prt_2(t_philo **philo, char **argv)
{
	pthread_mutex_t	*fork_right;
	int				i;

	i = 0;
	if (tester(philo, ft_atoi(argv[1])) == 0)
		return (0);
	fork_right = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!fork_right)
		return (free_errors_fork(philo, 0));
	philo[0]->to_free = fork_right;
	while (philo[i])
	{
		if (pthread_mutex_init(&(fork_right[i]), NULL) != 0)
			return (free_errors_fork(philo, i));
		if (i == 0)
			philo[ft_atoi(argv[1]) - 1]->fork_right = &(fork_right[i]);
		else
			philo[i - 1]->fork_right = &(fork_right[i]);
		if (i != 0 || ft_atoi(argv[1]) - 1 != 0)
			philo[i]->fork_left = &(fork_right[i]);
		philo[i]->wrt_prvlg = (*philo)->wrt_prvlg;
		philo[i]->testing = (*philo)->testing;
		i++;
	}
	return (1);
}

int	ft_left_forks(t_philo **philo, char **argv)
{
	pthread_mutex_t	*wrt_prvlg;
	pthread_mutex_t	*testing;

	wrt_prvlg = malloc(sizeof(pthread_mutex_t));
	(*philo)->wrt_prvlg = wrt_prvlg;
	if (!wrt_prvlg)
		return (0);
	testing = malloc(sizeof(pthread_mutex_t));
	(*philo)->testing = testing;
	if (!testing)
	{
		free(wrt_prvlg);
		return (0);
	}
	if (pthread_mutex_init(&(wrt_prvlg[0]), NULL) != 0)
		return (free_errors_2(*philo, 0));
	if (pthread_mutex_init(&(testing[0]), NULL) != 0)
		return (free_errors_2(*philo, 1));
	return (ft_lft_fork_prt_2(philo, argv));
}

void	ft_initialize_part_2(t_philo *philo, char **argv)
{
	philo->die = ft_atoi(argv[2]);
	philo->sleep = ft_atoi(argv[4]);
	philo->eat = ft_atoi(argv[3]);
	philo->total = ft_atoi(argv[1]);
	philo->last_meal = 0;
	philo->fork_left = NULL;
	philo->to_free = NULL;
	philo->to_free_2 = NULL;
	philo->testing = NULL;
	philo->wrt_prvlg = NULL;
}

int	pre_init(t_philo **philo)
{
	philo[0] = malloc(sizeof(t_philo));
	if (!philo[0])
		return (0);
	philo[0]->first_time = malloc(sizeof(int));
	if (!philo[0]->first_time)
	{
		free(philo[0]);
		return (0);
	}
	philo[0]->alive = malloc(sizeof(int));
	if (!philo[0]->alive)
	{
		free(philo[0]->first_time);
		free(philo[0]);
		return (0);
	}
	*philo[0]->alive = 1;
	*philo[0]->first_time = -1;
	return (1);
}

int	ft_initialize(t_philo **philo, char **argv)
{
	int	i;

	if (pre_init(&(philo[0])) == 0)
		return (0);
	i = 0;
	while (i != ft_atoi(argv[1]))
	{
		if (i != 0)
			philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (free_error(philo, i));
		philo[i]->alive = philo[0]->alive;
		philo[i]->first_time = philo[0]->first_time;
		philo[i]->nbr = i + 1;
		ft_initialize_part_2(philo[i], argv);
		i++;
		if (philo[0]->eat == 0 || philo[0]->die == 0 || philo[0]->sleep == 0)
			return (free_error(philo, i));
	}
	philo[i] = NULL;
	if (ft_left_forks(philo, argv) == 0)
		return (free_error(philo, i));
	return (1);
}
