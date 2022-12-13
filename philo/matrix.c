/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:50:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/12 22:06:37 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t	*fork_create(int n_of_philos);

int	dinner_start(t_table *table)
{
	pthread_t		*philo_threads;
	unsigned int	simul_start;
	unsigned int	i;
	
	table->philo_threads = ph_calloc(table->philos[0].n_of_philos,\
		 sizeof(pthread_t));
	if (test_alloc(philo_threads) != 0)
		return (-1);
	table->forks = fork_create(table->philos[0].n_of_philos);
	i = 0;
	simul_start = getcurrtime_ms();
	while (i < table->philos->n_of_philos)
	{
		table->philos[i].matrix_start = simul_start;
		table->philos[i].forks = table->forks;
		if (thread_start(&philo_threads[i], simulation,\
				 (void *) &table->philos[i]) != 0)
			return(-1);
		i++;
	}
	init_waiter_service();
	return (0);
}


int dinner_end(t_table *table) 
{
	int	i;

	i = 0;
	while (i < table->n_of_philos)
	{
		pthread_join(table->philo_threads[i], NULL);
		i++;
	}
	pthread_join(*table->waiter, NULL);
	pthread_mutex_destroy(table->philos[0].print_mutex);
	free(table->philos);
	return (0);
}

void	*simulation(void *param)
{
	t_philo			*philosopher;


	return (NULL);
}

pthread_mutex_t *fork_create(int n_of_philos)
{
	pthread_mutex_t		*forks;
	int					i;

	forks = ph_calloc(n_of_philos, sizeof(pthread_t));
	i = 0;
	while (i < n_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}
