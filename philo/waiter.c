/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:04:22 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/12 20:06:07 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <unistd.h>

#include <stdio.h>
void	*waiter_serve(void *param)
{
	// while no philo is dead do:
	// check if any philo changed its 'ask_to_eat' variable
	// if philo_id - 1 and philo_id forks are available then change the 'permission_to_eat' of that philo to 1
	int		i;
	t_table	*dinner_table;
	t_philo	*philo_list;

	dinner_table = (t_table *) param;
	philo_list = dinner_table->philos;
	while (1)
	{
		i = 0;	
		while (i < dinner_table->n_of_philos)
		{
			if (philo_list[i].waiter_lock != NULL)
				pthread_mutex_lock(philo_list[i].waiter_lock);
			else
				continue ;
			if (philo_list[i].state == PHILO_DEAD)
				return (NULL);
			if (philo_list[i].ask_permission == 1)
			{
				//printf("I'm running hot\n");
				if (philo_list[i - 1].permission_to_eat == 0 && philo_list[i + 1].permission_to_eat == 0)
				{
					if (philo_list[i].ticket_n < philo_list[i - 1].ticket_n && philo_list[i].ticket_n < philo_list[i + 1].ticket_n)
					{
						philo_list[i].ask_permission = 0;
						philo_list[i].permission_to_eat = 1;
						philo_list[i].ticket_n = 2147483647;	
					}
					else
					{
						philo_list[i].ask_permission = 0;
						philo_list[i].permission_to_eat = 0;
					}
				}		
			}
			pthread_mutex_unlock(philo_list[i].waiter_lock);
			i++;
		}
	}
	return (NULL);
}

t_table	*init_waiter_service()
{
	t_table		*dinner_table;

	dinner_table = ph_calloc(1, sizeof(t_table));
	dinner_table->n_of_philos = philo_info->n_of_philos;
	dinner_table->n_of_forks = philo_info->n_of_philos;
	dinner_table->philos = philos;
	dinner_table->waiter = ph_calloc(1, sizeof(pthread_t));
	if (!dinner_table->waiter)
		return (NULL);
	pthread_create(dinner_table->waiter, NULL, waiter_serve, dinner_table);
	return (dinner_table);
}

unsigned long	get_ticket()
{
	static unsigned long	ticket;

	ticket += 1;
	return (ticket);
}
