/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:50:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/13 02:35:54 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t	*fork_create(int n_of_philos);

int	dinner_start(t_table *table)
{
	unsigned int	simul_start;
	unsigned int	i;
	
	table->philo_threads = ph_calloc(table->philos[0].n_of_philos,\
		 sizeof(pthread_t));
	if (test_alloc(table->philo_threads) != 0)
		return (-1);
	table->forks = fork_create(table->philos[0].n_of_philos);
	i = 0;
	simul_start = getcurrtime_ms();
	init_waiter_service(table);
	while (i < table->philos->n_of_philos)
	{
		table->philos[i].matrix_start = simul_start;
		table->philos[i].forks = table->forks;
		if (thread_start(&table->philo_threads[i], simulation,\
				 (void *) &table->philos[i]) != 0)
			return(-1);
		i++;
	}
	return (0);
}

int dinner_end(t_table *table) 
{
	int	i;

	i = 0;
	pthread_join(*table->waiter, NULL);
	while (i < table->n_of_philos)
	{
		pthread_join(table->philo_threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(table->philos[0].print_mutex);
	free(table->philos);
	return (0);
}

#include <stdio.h>
void	*simulation(void *param)
{
	t_philo			*philo;
	
	philo = (t_philo *) param;
	while (check_alive(philo))
	{
		pthread_mutex_lock(philo->waiter_lock);
		if (philo->state == PHILO_THINK && \
			(philo->ask_permission == 0 && philo->permission_to_eat == 0))
		{
			philo->ask_permission = 1;
		}
		pthread_mutex_unlock(philo->waiter_lock);
		pthread_mutex_lock(philo->waiter_lock);
		if (philo->permission_to_eat == 1)
		{
			printf("I'm running cold\n");
			philo_take_lfork(philo);
			philo_take_rfork(philo);
			philo_eat_meal(philo);
		}
		else
			philo->ticket_n = get_ticket();
		pthread_mutex_unlock(philo->waiter_lock);
	}
	print_status(philo, "is dead");
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
