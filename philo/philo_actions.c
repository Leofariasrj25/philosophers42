/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:29:01 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/09 18:19:52 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <unistd.h>

int	philo_eat_meal(t_philo *philosopher)
{
	int	status;

	status = 0;
	if ((philosopher->has_rfork && philosopher->has_lfork) && philosopher->state != PHILO_EAT)
	{
		philosopher->state = PHILO_EAT;
		print_status(philosopher, "is eating");
		while (1)
		{
			if (elapsed_time_ms(philosopher->lt_eat) >= philosopher->tt_die)
			{
				philosopher->state = PHILO_DEAD;
				return (PHILO_DEAD);
			}
			if (elapsed_time_ms(philosopher->lt_eat) >= philosopher->tt_eat)
			{
				status = philo_sleep();
				return (status);
			}
		}
	}
	return (0);
}

int		philo_sleep(t_philo *philosopher)
{
	print_status(philosopher, "is sleeping");
	philosopher->state = PHILO_SLEEP;
	pthread_mutex_unlock(philosopher->forks[0]);
	philosopher->has_lfork = 0;
	pthread_mutex_unlock(philosopher->forks[1]);
	philosopher->has_rfork = 0;
}

int	philo_take_lfork(t_philo *philosopher)
{	
	if (philosopher->state != PHILO_EAT && philosopher->has_lfork == 0)
	{
		pthread_mutex_lock(philosopher->forks[philosopher->philo_id - 1]);
		print_status(philosopher, "has taken left fork");
		return (0);
	}
	return (-1);
}

int	philo_take_rfork(t_philo *philosopher)
{
	if (philosopher->state != PHILO_EAT && philosopher->has_rfork == 0)
	{
		pthread_mutex_lock(philosopher->forks[philosopher->philo_id - 1]);
		print_status(philosopher, "has taken right fork");
	}
	return (-1);
}
