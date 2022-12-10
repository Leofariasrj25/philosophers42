/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:29:01 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/09 23:45:03 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <unistd.h>

int	philo_eat_meal(t_philo *philosopher)
{
	int	status;

	status = 0;
	if ((philosopher->has_rfork && philosopher->has_lfork) \
		&& (philosopher->state == PHILO_THINK))
	{
		philosopher->state = PHILO_EAT;
		philosopher->lt_eat = getcurrtime_ms(); 
		print_status(philosopher, "is eating");
		while (1)
		{
			if (elapsed_time_ms(philosopher->lt_eat) >= philosopher->tt_die && philosopher->state == PHILO_EAT)
			{
				philosopher->state = PHILO_DEAD;
				return (PHILO_DEAD);
			}
			if (elapsed_time_ms(philosopher->lt_eat) >= philosopher->tt_eat && philosopher->state == PHILO_EAT)
			{
				status = philo_sleep(philosopher);
				return (status);
			}
		}
	}
	return (0);
}

int		philo_sleep(t_philo *philosopher)
{
	unsigned int	c_time;
	unsigned long	sleep_time;

	if (!philosopher)
		return (-1);
	print_status(philosopher, "is sleeping");
	philosopher->state = PHILO_SLEEP;
	pthread_mutex_unlock(philosopher->lfork_mutex);
	philosopher->has_lfork = 0;
	pthread_mutex_unlock(philosopher->rfork_mutex);
	philosopher->has_rfork = 0;
	c_time = getcurrtime_ms(); 
	if (c_time + philosopher->tt_sleep < c_time + philosopher->tt_die)
	{
		usleep(philosopher->tt_sleep * 1000);
		return (PHILO_THINK);
	}
	else	
	{
		sleep_time = (c_time + philosopher->tt_sleep) - (c_time + philosopher->tt_die);
		usleep(sleep_time * 1000);
		return (PHILO_DEAD);
	}
}

#include <stdio.h>
int	philo_take_lfork(t_philo *philosopher)
{	
	int	lfork_i;
	
	if (!philosopher)
		return (-1);
	lfork_i = (philosopher->philo_id + 1) % philosopher->n_of_philos; 
	printf("lfork_i %d\n", lfork_i);
	if (philosopher->state == PHILO_THINK && philosopher->has_lfork == 0)
	{
		pthread_mutex_lock(philosopher->forks[lfork_i - 1]);
		philosopher->lfork_mutex = philosopher->forks[lfork_i - 1];
		philosopher->has_lfork = 1;
		print_status(philosopher, "has taken left fork");
		return (0);
	}
	return (-1);
}

int	philo_take_rfork(t_philo *philosopher)
{
	int	rfork_i;

	if (!philosopher)
		return (-1);
	rfork_i = (philosopher->philo_id + philosopher->n_of_philos) % philosopher->n_of_philos; 
	if (philosopher->state == PHILO_THINK && philosopher->has_rfork == 0)
	{
		printf("rfork_i %d\n", rfork_i);
		pthread_mutex_lock(philosopher->forks[rfork_i - 1]);
		philosopher->rfork_mutex = philosopher->forks[rfork_i - 1];
		philosopher->has_rfork = 1;
		print_status(philosopher, "has taken right fork");
		return (0);
	}
	return (-1);
}
