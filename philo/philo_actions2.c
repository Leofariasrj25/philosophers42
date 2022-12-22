/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 22:56:24 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/22 14:32:10 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

int	add_total_meals(t_philo *philosopher)
{
	if (philosopher->min_meals == -1)
		return (-1);
	if (philosopher->n_of_meals == philosopher->min_meals)
		return (check_total_meals(philosopher));
	pthread_mutex_lock(philosopher->banquet->dinner_mutex);
	philosopher->n_of_meals = philosopher->n_of_meals + 1;
	philosopher->banquet->curr_meals = philosopher->banquet->curr_meals + 1;
	if (philosopher->banquet->curr_meals == philosopher->banquet->total_meals)
	{
		philosopher->banquet->is_over = 1;
		pthread_mutex_unlock(philosopher->banquet->dinner_mutex);
		return (1);
	}
	pthread_mutex_unlock(philosopher->banquet->dinner_mutex);
	return (0);
}

int	check_total_meals(t_philo *philosopher)
{
	pthread_mutex_lock(philosopher->banquet->dinner_mutex);
	if (philosopher->min_meals == -1)
		return (0);
	if (philosopher->banquet->curr_meals == philosopher->banquet->total_meals)
	{	
		pthread_mutex_unlock(philosopher->banquet->dinner_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philosopher->banquet->dinner_mutex);
		return (0);
	}
}

long	get_checkpoint_ms(t_philo *philosopher)
{
	if (philosopher->lt_eat == 0)
		return (philosopher->matrix_start);
	else
		return (philosopher->lt_eat);
}

int	has_forks(t_philo *philosopher)
{
	if ((philosopher->lfork_mutex != NULL && philosopher->rfork_mutex != NULL) \
		&& (philosopher->state == PHILO_THINK))
		return (1);
	else
		return (0);
}
