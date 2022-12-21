/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:50:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/21 16:28:49 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <unistd.h>

pthread_mutex_t	*fork_create(int n_of_philos);
pthread_mutex_t	*create_state_mutex(void);
void			philo_think(t_philo *philo);
int				philo_lifecycle(t_philo *philo);

int	dinner_start(t_table *table)
{
	long	simul_start;
	int		i;

	table->philo_threads = (pthread_t *) ph_calloc(table->n_of_philos, \
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
		if (pthread_create(&table->philo_threads[i], NULL, simulation, \
			(void *) &table->philos[i]) != 0)
		{
			put_err_str("{ERROR}: error during thread creation\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	dinner_end(t_table *table)
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
	t_philo	*philo;
	int		philo_status;	

	philo = (t_philo *) param;
	if (philo->philo_id % 2 == 0)
	{
		print_status(philo, "is thinking", PHILO_THINK);
		micro_sleep(philo->tt_eat, philo);
	}
	while (1)
	{
		philo_status = philo_lifecycle(philo);
		if (philo_status == PHILO_DEAD || philo_status == MATRIX_END)
			break ;
	}
	philo_put_forks_down(philo);
	return (NULL);
}

int	philo_lifecycle(t_philo *philo)
{
	int		philo_status;	

	philo_status = check_alive(philo);
	if (philo_status == PHILO_DEAD)
	{
		print_status(philo, "died", PHILO_DEAD);
		return (PHILO_DEAD);
	}	
	if (philo_status == MATRIX_END)
		return (MATRIX_END);
	philo_take_forks(philo);
	philo_status = philo_eat_meal(philo);
	if (philo_status == MATRIX_END)
		return (MATRIX_END);
	philo_think(philo);
	return (0);
}

pthread_mutex_t	*fork_create(int n_of_philos)
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
