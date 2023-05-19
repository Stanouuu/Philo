/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:42:00 by sbarrage          #+#    #+#             */
/*   Updated: 2023/03/20 16:02:14 by sbarrage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			*philo[200];
	pthread_t		*t;
	int				i;
	int				j;

	if (argc != 5 || all_nbr(argv) == 0 || ft_atoi(argv[1]) == 0)
		return (0);
	j = ft_atoi(argv[1]);
	if (j > 200)
		return (1);
	i = 0;
	if (ft_initialize(philo, argv) == 0)
		return (2);
	pthread_mutex_lock(philo[0]->testing);
	while (philo[i])
	{
		t = &(philo[i]->thread);
		if (pthread_create(t, NULL, ft_philo, (void *) philo[i]) != 0)
			order_66(philo);
		i++;
	}
	if (*(*philo)->alive == 1)
		ft_checker(philo);
	ft_free(philo, i);
	return (3);
}
