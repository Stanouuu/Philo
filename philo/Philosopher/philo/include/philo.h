/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:54:19 by sbarrage          #+#    #+#             */
/*   Updated: 2023/03/19 17:41:28 by sbarrage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "ft_printf.h"
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_philo
{
	int					nbr;
	int					eat;
	int					sleep;
	int					die;
	int					*alive;
	int					total;
	pthread_mutex_t		*fork_right;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*wrt_prvlg;
	pthread_mutex_t		*testing;
	pthread_mutex_t		*inditest;
	pthread_mutex_t		*to_free;
	pthread_mutex_t		*to_free_2;
	int					last_meal;
	int					*first_time;
	pthread_t			thread;
}	t_philo;

void	*ft_philo(void *voi);
int		tester(t_philo **philo, int k);
int		free_errors_test(t_philo *philo, int i);
int		free_errors_2(t_philo *philo, int i);
int		free_errors_fork(t_philo **philo, int i);
int		free_error(t_philo **philo, int i);
void	ft_free(t_philo **philo, int i);
int		ft_print_action(t_philo *philo, char *str, int eat);
int		ft_isdigit(int c);
int		all_nbr(char **argv);
int		ft_atoi(const char *str);
int		ft_initialize(t_philo **philo, char **argv);
int		philo_test(t_philo *philo);
void	order_66(t_philo **philos);
void	ft_checker(t_philo **checker);

#endif