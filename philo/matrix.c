/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:50:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/05 15:41:02 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <stdio.h>

void	*simulation(void *param)
{
	t_philo			*philosopher;
	struct timeval	current_time;
	long			lt_eat_msec;
	long			present_time;

	philosopher = (t_philo *) param;
	gettimeofday(&current_time, NULL);
	lt_eat_msec = current_time.tv_sec * 1000;
 	while (1)
	{
		gettimeofday(&current_time, NULL);
		present_time = current_time.tv_sec;
		if ((present_time - lt_eat_msec) < (philosopher->tt_die / 1000))
		{
			print_status(philosopher, "is thinking");
		}
		else
			break ;
	}
	printf("Philosopher %d is dead\n", philosopher->philo_id);
	return (NULL);
}

pthread_t	**dinner_start(t_philo *philos, t_meta *philo_info, int *op_code)
{
	unsigned int		i;
	struct timeval		start;
	pthread_t			**philo_threads;
	long				timestamp;

	i = 0;
	philo_threads = malloc(sizeof(pthread_t *) * philo_info->n_of_philos);
	if (!philo_threads)
	{
		put_err_str("{ERROR}: malloc malfunction\n");
		*op_code = -1;
		return (NULL);
	}
	gettimeofday(&start, NULL);
	timestamp = start.tv_sec * 1000;
	while (i < philo_info->n_of_philos)
	{
		philos[i].matrix_start = timestamp;
		philo_threads[i] = malloc(sizeof(pthread_t));
		if (pthread_create(philo_threads[i], \
			 NULL, simulation, (void *) &philos[i]) != 0)
		{
			put_err_str("{ERROR}: error during thread creation\n");
			*op_code = -1;
			return (NULL);
		}
		i++;
	}
	return (philo_threads);
}

int dinner_end(t_philo *philos, pthread_t **philo_threads, int philo_size) 
{
	int	i;

	i = 0;
	while (i < philo_size)
	{
		pthread_join(*philo_threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(philos[0].print_mutex);
	free(philos);
	return (0);
}
