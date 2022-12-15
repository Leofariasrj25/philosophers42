/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:50:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/15 17:48:43 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t	*fork_create(int n_of_philos);

int	dinner_start(t_table *table)
{
	unsigned int	simul_start;
	int	i;
	
	table->philo_threads = (pthread_t *) ph_calloc(table->n_of_philos,\
		 sizeof(pthread_t));
	if (test_alloc(table->philo_threads) != 0)
		return (-1);
	table->forks = fork_create(table->n_of_philos);
	simul_start = getcurrtime_ms();
	i = 0;
	while (i < table->n_of_philos)
	{
		table->philos[i].matrix_start = simul_start;
		table->philos[i].forks = table->forks;
		if (pthread_create(&table->philo_threads[i], NULL, simulation,\
				 (void *) &table->philos[i]) != 0)
			printf("Wrong accessn\n");

		i++;
	}
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
	while (i < table->n_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table->philo_threads);
	free(table->philos);
	return (0);
}

#include <stdio.h>
void	*simulation(void *param)
{
	t_philo			*philo;
	
	philo = (t_philo *) param;
	if (philo->philo_id % 2 != 0)
	{
		print_status(philo, "is thinking");
		micro_sleep(10);
	}
	while (1)
	{
		if (check_alive(philo) == 1)
		{	
			philo_take_lfork(philo);
			philo_take_rfork(philo);
			if (philo->lfork_mutex == NULL && philo->rfork_mutex == NULL)
				print_status(philo, "is thinking");
			if (philo_eat_meal(philo) == PHILO_THINK) 
				print_status(philo, "is thinking");
			else
				break ;
		}
		else
		{
			break ;
		}
		printf("Things are going crazy!\n");
	}
	philo_put_forks_down(philo);
	philo->state = PHILO_DEAD;
	print_status(philo, "is dead");
	return (NULL);
}

pthread_mutex_t *fork_create(int n_of_philos)
{
	pthread_mutex_t		*forks;
	int					i;

	forks = ph_calloc(n_of_philos, sizeof(*forks));
	i = 0;
	while (i < n_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}
