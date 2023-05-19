/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:29:02 by sbarrage          #+#    #+#             */
/*   Updated: 2023/03/19 17:41:15 by sbarrage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_action(t_philo *philo, char *str, int eat)
{
	struct timeval	current;
	int				time;
	int				a;

	pthread_mutex_lock(philo->testing);
	gettimeofday(&current, NULL);
	a = (current.tv_usec + (current.tv_sec % 1000) * 1000000);
	time = (a - *philo->first_time) / 1000;
	if (eat == 1)
		philo->last_meal = time;
	if (philo_test(philo) == 0)
		return (0);
	pthread_mutex_lock(philo->wrt_prvlg);
	ft_printf("%d %d %s", time, philo->nbr, str);
	pthread_mutex_unlock(philo->wrt_prvlg);
	pthread_mutex_unlock(philo->testing);
	return (1);
}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

int	all_nbr(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	tester(t_philo **philo, int k)
{
	int				i;
	pthread_mutex_t	*inditest;

	i = 0;
	inditest = malloc(sizeof(pthread_mutex_t) * k);
	if (!inditest)
		return (free_errors_2(*philo, 0));
	philo[0]->to_free_2 = inditest;
	while (philo[i])
	{
		if (pthread_mutex_init(&(inditest[i]), NULL) != 0)
			return (free_errors_test((*philo), i));
		philo[i]->inditest = &(inditest[i]);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long int	i;
	long int	neg;
	long int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * neg);
}
