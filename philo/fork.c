/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:29:29 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/20 17:43:32 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

int	philo_take_lfork(t_philo *philosopher);
int	philo_take_rfork(t_philo *philosopher);

int	philo_take_forks(t_philo *philosopher)
{
	if (philosopher->philo_id == philosopher->n_of_philos)
	{
		if (philo_take_lfork(philosopher) == -1)
			return (-1);
		if (philo_take_rfork(philosopher) == -1)
			return (-1);
	}
	else
	{
		if (philo_take_rfork(philosopher) == -1)
			return (-1);
		if (philo_take_lfork(philosopher) == -1)
			return (-1);
	}
	return (0);
}

int	philo_take_lfork(t_philo *philo)
{	
	if (!philo)
		return (-1);
	if (philo->state == PHILO_THINK && philo->lfork_mutex == NULL)
	{
		if (pthread_mutex_lock(&philo->forks[philo->philo_id - 1]) == 0)
		{
			if (check_is_dinner_over(philo) == 1)
				return (-1);
			if (check_alive(philo) == 0)
				return (PHILO_DEAD);
			philo->lfork_mutex = &philo->forks[philo->philo_id - 1];
			print_status(philo, "has taken a fork", PHILO_THINK);
			return (1);
		}
	}
	return (0);
}

unsigned int	get_right_index(t_philo *ph)
{
	return ((ph->philo_id - 2 + ph->n_of_philos) % ph->n_of_philos);
}

int	philo_take_rfork(t_philo *philo)
{
	if (!philo)
		return (-1);
	if (philo->n_of_philos == 1)
		return (0);
	if (philo->state == PHILO_THINK && philo->rfork_mutex == NULL)
	{
		if (pthread_mutex_lock(&philo->forks[get_right_index(philo)]) == 0)
		{
			if (check_is_dinner_over(philo) == 1)
				return (-1);
			if (check_alive(philo) == 0)
				return (PHILO_DEAD);
			philo->rfork_mutex = &philo->forks[get_right_index(philo)];
			print_status(philo, "has taken a fork", PHILO_THINK);
			return (1);
		}
	}
	return (0);
}

int	philo_put_forks_down(t_philo *philosopher)
{
	if (philosopher->rfork_mutex != NULL)
	{
		pthread_mutex_unlock(philosopher->rfork_mutex);
		philosopher->rfork_mutex = NULL;
	}
	if (philosopher->lfork_mutex != NULL)
	{
		pthread_mutex_unlock(philosopher->lfork_mutex);
		philosopher->lfork_mutex = NULL;
	}
	return (0);
}
