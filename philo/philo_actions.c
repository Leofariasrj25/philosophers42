/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:29:01 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/16 20:05:58 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <unistd.h>

int	philo_eat_meal(t_philo *philosopher)
{
	if ((philosopher->lfork_mutex != NULL && philosopher->rfork_mutex != NULL) \
		&& (philosopher->state == PHILO_THINK))
	{
		philosopher->state = PHILO_EAT;
		philosopher->lt_eat = getcurrtime_ms();
		print_status(philosopher, "is eating");
		while (1)
		{
			if (elapsed_time_since(philosopher->lt_eat) >= philosopher->tt_die \
				&& philosopher->state == PHILO_EAT)
			{
				philosopher->state = PHILO_DEAD;
				return (PHILO_DEAD);
			}
			if (elapsed_time_since(philosopher->lt_eat) >= philosopher->tt_eat \
				&& philosopher->state == PHILO_EAT)
			{
				return (philo_sleep(philosopher));
			}
		}
	}
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	unsigned int	c_time;
	unsigned long	sleep_time;

	if (!philo)
		return (-1);
	print_status(philo, "is sleeping");
	philo->state = PHILO_SLEEP;
	philo_put_forks_down(philo);
	c_time = getcurrtime_ms();
	if (c_time + philo->tt_sleep < c_time + philo->tt_die)
	{
		micro_sleep(philo->tt_sleep * 1000);
		return (PHILO_THINK);
	}
	else
	{
		sleep_time = (c_time + philo->tt_sleep) - (c_time + philo->tt_die);
		micro_sleep(sleep_time * 1000);
		return (PHILO_DEAD);
	}
}

int	philo_take_lfork(t_philo *philosopher)
{	
	if (!philosopher)
		return (-1);
	if (philosopher->philo_id == philosopher->n_of_philos)
		return (philo_take_rfork(philosopher));
	if (philosopher->state == PHILO_THINK && philosopher->lfork_mutex == NULL)
	{
		if (pthread_mutex_lock(&philosopher->forks[philosopher->philo_id - 1]) == 0)
		{
			philosopher->lfork_mutex = &philosopher->forks[philosopher->philo_id - 1];
			print_status(philosopher, "has taken left fork");
			return (0);
		}
	}
	return (-1);
}

unsigned int	get_right_index(t_philo *ph)
{
	return ((ph->philo_id - 2 + ph->n_of_philos) % ph->n_of_philos);
}

int	philo_take_rfork(t_philo *philo)
{
	if (!philo)
		return (-1);
	if (philo->philo_id == philo->n_of_philos)
		return (philo_take_lfork(philo));
	if (philo->state == PHILO_THINK && philo->rfork_mutex == NULL)
	{
		if (pthread_mutex_lock(&philo->forks[get_right_index(philo)]) == 0)
		{
			philo->rfork_mutex = &philo->forks[get_right_index(philo)];
			print_status(philo, "has taken right fork");
			return (0);
		}
	}
	return (-1);
}

#include <stdio.h>
int	check_alive(t_philo *philosopher)
{
	long			time_diff;
	unsigned int	ctime_ms;

	pthread_mutex_lock(philosopher->print_mutex);
	ctime_ms = getcurrtime_ms();
	if (philosopher->lt_eat == 0)
		time_diff = (long)(ctime_ms - philosopher->matrix_start);
	else
		time_diff = (long)(ctime_ms - philosopher->lt_eat);
	printf("%ld\n", time_diff);
	pthread_mutex_unlock(philosopher->print_mutex);
	if (((unsigned int) time_diff) < philosopher->tt_die)
		return (1);
	else
		return (0);
}

int	philo_put_forks_down(t_philo *philosopher)
{
	if (philosopher->lfork_mutex != NULL)
	{
		pthread_mutex_unlock(philosopher->lfork_mutex);
		philosopher->lfork_mutex = NULL;
	}
	if (philosopher->rfork_mutex != NULL)
	{
		pthread_mutex_unlock(philosopher->rfork_mutex);
		philosopher->rfork_mutex = NULL;
	}
	return (0);
}
