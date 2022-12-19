/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:04:40 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/17 23:20:41 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

void	destroy_all_philos(t_philo *philos, int n_of_philos)
{
	if (!philos || n_of_philos == 0)
		return ;
	destroy_all_forks(philos[0].forks, n_of_philos);
	destroy_philo_locks(philos);
	free(philos);
}

void	destroy_all_forks(pthread_mutex_t *forks, int n_of_forks)
{
	int	i;

	if (!forks || n_of_forks == 0)
		return ;
	i = 0;
	while (i < n_of_forks)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

void	destroy_philo_locks(t_philo *philos)
{
	if (!philos)
		return ;
	if (philos[0].print_mutex != NULL)
	{
		pthread_mutex_destroy(philos[0].print_mutex);
		free(philos[0].print_mutex);
	}
	if (philos[0].state_mutex != NULL)
	{
		pthread_mutex_destroy(philos[0].state_mutex);
		free(philos[0].print_mutex);
	}
}

/*void	destroy_table(t_table *table)
{
	if (!table->dinner_lock)
		return ;
	pthread_mutex_destroy(table->dinner_lock);
	free(table->dinner_lock);
}*/
