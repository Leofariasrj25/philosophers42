/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:50:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/19 02:44:15 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <unistd.h>

pthread_mutex_t	*fork_create(int n_of_philos);
pthread_mutex_t *create_state_mutex(void);

int	dinner_start(t_table *table)
{
	long	simul_start;
	int		i;
	
	table->philo_threads = (pthread_t *) ph_calloc(table->n_of_philos,\
		 sizeof(pthread_t));
	if (!table->philo_threads)
		return (-1);
	table->forks = fork_create(table->n_of_philos);
	simul_start = get_currtime_ms();
	i = 0;
	while (i < table->n_of_philos)
	{
		table->philos[i].banquet = table->banquet;
		table->philos[i].matrix_start = simul_start;
		table->philos[i].lt_eat = 0;
		table->philos[i].forks = table->forks;
		if (pthread_create(&table->philo_threads[i], NULL, simulation,\
				 (void *) &table->philos[i]) != 0)
			printf("Wrong access\n");

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
	pthread_mutex_destroy(table->philos[0].print_mutex);
	pthread_mutex_destroy(table->banquet->dinner_mutex);
	free(table->philos[0].print_mutex);
	free(table->banquet->dinner_mutex);
	free(table->banquet);
	free(table->forks);
	free(table->philo_threads);
	free(table->philos);
	return (0);
}

void	*simulation(void *param)
{
	t_philo			*philo;
	
	philo = (t_philo *) param;
	if (philo->philo_id % 2 != 0)
	{
		print_status(philo, "is thinking", PHILO_THINK);
		usleep(60);
	}
	else 
		print_status(philo, "is thinking", PHILO_THINK);
	while (1)
	{
		int philo_status = check_alive(philo);
		if (philo_status == 0)
		{
			print_status(philo, "is dead", PHILO_DEAD);
			break ;
		}	
		if (philo_status == -1)
			break ;
		if (philo_take_forks(philo) == -1)
			break ;
		philo_status = philo_eat_meal(philo);
		if (philo_status == -1)
			break ;
		if ((philo->lfork_mutex == NULL && philo->rfork_mutex == NULL) && philo->state == PHILO_THINK)
			print_status(philo, "is thinking", PHILO_THINK);
	}
	philo_put_forks_down(philo);
	return (NULL);
}

int	check_is_dinner_over(t_philo *philo)
{
	int	is_dinner_over;

	pthread_mutex_lock(philo->banquet->dinner_mutex);
	if (philo->banquet->is_over == 1)
		is_dinner_over = 1;
	else
		is_dinner_over = 0;
	pthread_mutex_unlock(philo->banquet->dinner_mutex);	
	return (is_dinner_over);
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

void	set_dinner_over(t_philo *philosopher)
{
	pthread_mutex_lock(philosopher->print_mutex);
	pthread_mutex_lock(philosopher->banquet->dinner_mutex);
	philosopher->banquet->is_over = 1;
	pthread_mutex_unlock(philosopher->banquet->dinner_mutex);
	pthread_mutex_unlock(philosopher->print_mutex);
}
