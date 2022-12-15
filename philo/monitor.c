/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:25:28 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/15 17:54:33 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

void	*monitor_watch(void *param)
{
	t_table	*dinner_table;
	t_philo *philo;
	int		i;	

	dinner_table = (t_table *) param;
	while (42)
	{
		i = 0;
		while (i < dinner_table->n_of_philos)
		{
			philo = &dinner_table->philos[i];
			if (pthread_mutex_lock(philo->state_lock))
			{
				if (philo->state == PHILO_DEAD)
				{
					pthread_mutex_lock(dinner_table->dinner_lock);
					dinner_table->is_dinner_over = 1;	
					pthread_mutex_unlock(dinner_table->dinner_lock);
					pthread_mutex_unlock(philo->state_lock);
					return (NULL);
				}
				pthread_mutex_unlock(philo->state_lock);
			}
			i++;
		}
	}
	return (NULL);
}

int monitor_start(t_table *dinner_table)
{
	if (!dinner_table)
		return (-1);
	dinner_table->monitor_thread = ph_calloc(1, sizeof(pthread_t));
	if (!dinner_table->monitor_thread)
		return (-1);
	if (pthread_create(dinner_table->monitor_thread, NULL, monitor_watch, \
		(void *) dinner_table) != 0)
	{
		free(dinner_table->monitor_thread);
		return (-1);
	}
	return (0);
}
