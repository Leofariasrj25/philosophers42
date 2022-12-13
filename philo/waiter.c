/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:04:22 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/13 02:09:10 by lfarias-         ###   ########.fr       */
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
			if (philo_list[i].state == PHILO_DEAD)
				return (NULL);
			if (philo_list[i].waiter_lock != NULL)
				pthread_mutex_lock(philo_list[i].waiter_lock);
			else
				continue ;
			if (philo_list[i].ask_permission == 1)
			{
				int left_ph = philo_list[i].philo_id;
				int right_ph = (philo_list[i].philo_id - 2 + philo_list[i].n_of_philos) % philo_list[i].n_of_philos;
				if (i == 0)
				{
					left_ph = 1;
					right_ph = 4;
				}
				if (i == dinner_table->n_of_philos - 1)
				{
					left_ph = 0;
					right_ph = dinner_table->n_of_philos - 2;	
				}
				printf("I'm running hot\n");
				if (philo_list[left_ph].permission_to_eat == 0 && philo_list[right_ph].permission_to_eat == 0)
				{
					/*printf("I'm running chilli\n");
					printf("left philo [%d] ticket id: %ld\n", left_ph, philo_list[left_ph].ticket_n);
					printf("right philo [%d] ticket id: %ld\n", right_ph, philo_list[right_ph].ticket_n);
					printf("the current philo id ticket id: %ld\n", philo_list[i].ticket_n);*/
					if (philo_list[i].ticket_n < philo_list[left_ph].ticket_n && philo_list[i].ticket_n < philo_list[right_ph].ticket_n)
					{
						printf("I'm running tired\n");
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

void	init_waiter_service(t_table *dinner_table)
{
	dinner_table->n_of_philos = dinner_table->philos[0].n_of_philos; 
	dinner_table->n_of_forks = dinner_table->philos[0].n_of_philos;
	dinner_table->waiter = ph_calloc(1, sizeof(pthread_t));
	if (!dinner_table->waiter)
		return ;
	pthread_create(dinner_table->waiter, NULL, waiter_serve, dinner_table);
}

unsigned long	get_ticket()
{
	static unsigned long	ticket;

	ticket += 1;
	return (ticket);
}
