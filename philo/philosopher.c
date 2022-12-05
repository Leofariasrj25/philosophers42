/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:51:17 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/05 15:56:10 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

t_philo	*philo_create(t_meta *philo_info)
{
	unsigned int	i;
	t_philo			*philos;

	philos = malloc(sizeof(t_philo) * philo_info->n_of_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < philo_info->n_of_philos)
	{
		philos[i].philo_id = i;
		philos[i].tt_die = philo_info->tt_die;
		philos[i].tt_eat = philo_info->tt_eat;
		philos[i].tt_sleep = philo_info->tt_sleep;
		philos[i].min_meals = philo_info->min_meals;
		philos[i].state_change = 0;
		philos[i].state = PHILO_THINK; 
		philos[i].lt_eat = 0;
		philos[i].lt_sleep = 0;
		philos[i].print_mutex = &philo_info->print_mutex;
		i++;
	}
	return (philos);
}
