/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:50:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/09 22:52:33 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <stdio.h>
#include <unistd.h>

int				check_alive(t_philo *philosopher);
pthread_mutex_t	**fork_create(int n_of_philos);

pthread_t	**dinner_start(t_philo *philos, t_meta *philo_info, int *op_code)
{
	unsigned int		i;
	struct timeval		start;
	pthread_t			**philo_threads;
	long				timestamp;
	pthread_mutex_t		**forks;

	philo_threads = malloc(sizeof(pthread_t *) * philo_info->n_of_philos);
	if (!philo_threads)
	{
		put_err_str("{ERROR}: malloc malfunction\n");
		*op_code = -1;
		return (NULL);
	}
	i = 0;
	gettimeofday(&start, NULL);
	timestamp = start.tv_sec * 1000;
	forks = fork_create(philo_info->n_of_philos);
	while (i < philo_info->n_of_philos)
	{
		philos[i].matrix_start = timestamp;
		philos[i].forks = forks;
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

void	*simulation(void *param)
{
	t_philo			*philosopher;
	int				philo_status;

	philosopher = (t_philo *) param;
	while (1)
	{
		if (check_alive(philosopher))
		{
			philo_take_lfork(philosopher);
			philo_take_rfork(philosopher);
			philo_status = philo_eat_meal(philosopher);
			if(philo_status == PHILO_THINK)	
			{
				philosopher->state = PHILO_THINK;
				print_status(philosopher, "is thinking");	
			}
		}
		else
		{
			print_status(philosopher, "is dead");
			return (NULL);
		}
	}
	return (NULL);
}

int check_alive(t_philo *philosopher)
{
	struct timeval	current_time;
	long			simul_start;
	long			present_time;
	int				dead_or_alive;

	pthread_mutex_lock(philosopher->print_mutex);
	gettimeofday(&current_time, NULL);	
	present_time = current_time.tv_sec * 1000;
	simul_start = philosopher->matrix_start;
	if ((present_time - simul_start) < (philosopher->tt_die / 1000))
		dead_or_alive = 1;
	else
		dead_or_alive = 0;
	pthread_mutex_unlock(philosopher->print_mutex);
	return (dead_or_alive);

}

pthread_mutex_t **fork_create(int n_of_philos)
{
	pthread_mutex_t		**forks;
	pthread_mutex_t		*fork;
	int					i;

	forks = malloc(sizeof(pthread_mutex_t *) * (n_of_philos + 1));
	i = 0;
	while (i < n_of_philos)
	{
		forks[i] = fork;
		fork = malloc(sizeof(pthread_mutex_t)); 
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
	forks[i] = NULL;
	return (forks);
}

