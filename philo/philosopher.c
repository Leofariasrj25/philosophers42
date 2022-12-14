/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:51:17 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/19 21:48:51 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <pthread.h>

#define N_OF_PHILOS 0
#define TT_DIE 1
#define TT_EAT 2
#define TT_SLEEP 3
#define MIN_MEALS 4

int				load_meta(t_philo *philosopher, long *values);
int				load_defaults(int p_id, t_philo *ph, pthread_mutex_t *print_m);
pthread_mutex_t	*create_print_mutex(void);
void			destroy_resources(void *philos, pthread_mutex_t *print_mutex);

t_philo	*philo_create(long *values)
{
	int				i;
	t_philo			*philos;
	pthread_mutex_t	*print_mutex;

	i = -1;
	philos = malloc(values[N_OF_PHILOS] * sizeof(*philos));
	if (!philos)
		return (NULL);
	print_mutex = create_print_mutex();
	if (!print_mutex)
	{
		free(philos);
		return (NULL);
	}
	while (++i < values[N_OF_PHILOS])
	{
		load_meta(&philos[i], values);
		if (load_defaults(i + 1, &philos[i], print_mutex) != 0)
		{
			destroy_resources(philos, print_mutex);
			return (NULL);
		}
	}
	return (philos);
}

void	destroy_resources(void *philos, pthread_mutex_t *print_mutex)
{
	free(philos);
	pthread_mutex_destroy(print_mutex);
	free(print_mutex);
}

int	load_defaults(int p_id, t_philo *philo, pthread_mutex_t *p_mutex)
{
	philo->philo_id = p_id;
	philo->state = PHILO_THINK;
	philo->lt_eat = 0;
	philo->lfork_mutex = NULL;
	philo->rfork_mutex = NULL;
	philo->print_mutex = p_mutex;
	return (0);
}

int	load_meta(t_philo *philosopher, long *values)
{
	if (!philosopher || !values)
		return (-1);
	philosopher->n_of_philos = values[N_OF_PHILOS];
	philosopher->tt_die = values[TT_DIE];
	philosopher->tt_eat = values[TT_EAT];
	philosopher->tt_sleep = values[TT_SLEEP];
	philosopher->min_meals = values[MIN_MEALS];
	philosopher->n_of_meals = 0;
	return (0);
}

pthread_mutex_t	*create_print_mutex(void)
{
	pthread_mutex_t	*print_mutex;

	print_mutex = ph_calloc(1, sizeof(pthread_mutex_t));
	if (mutex_start(print_mutex) != 0)
		return (NULL);
	return (print_mutex);
}
