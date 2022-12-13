/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:29:01 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/12 23:25:17 by lfarias-         ###   ########.fr       */
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
			if (elapsed_time_ms(philosopher->lt_eat) >= philosopher->tt_die \
				&& philosopher->state == PHILO_EAT)
			{
				philosopher->state = PHILO_DEAD;
				return (PHILO_DEAD);
			}
			if (elapsed_time_ms(philosopher->lt_eat) >= philosopher->tt_eat \
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
	if (philo->lfork_mutex != NULL)
		pthread_mutex_unlock(philo->lfork_mutex);
	philo->lfork_mutex = NULL;
	if (philo->rfork_mutex != NULL)
		pthread_mutex_unlock(philo->rfork_mutex);
	philo->rfork_mutex = NULL;
	philo->permission_to_eat = 0;
	philo->ask_permission = 0;
	c_time = getcurrtime_ms();
	if (c_time + philo->tt_sleep < c_time + philo->tt_die)
	{
		usleep(philo->tt_sleep * 1000);
		return (PHILO_THINK);
	}
	else
	{
		sleep_time = (c_time + philo->tt_sleep) - (c_time + philo->tt_die);
		usleep(sleep_time * 1000);
		return (PHILO_DEAD);
	}
}

int	philo_take_lfork(t_philo *philosopher)
{	
	int	lfork_i;

	if (!philosopher)
		return (-1);
	lfork_i = philosopher->philo_id - 1;
	if (philosopher->state == PHILO_THINK && philosopher->lfork_mutex == 0)
	{
		if (pthread_mutex_lock(&philosopher->forks[lfork_i]) == 0)
		{
			philosopher->lfork_mutex = &philosopher->forks[lfork_i];
			print_status(philosopher, "has taken left fork");
			return (0);
		}
	}
	return (-1);
}

int	philo_take_rfork(t_philo *philo)
{
	int	rfork_i;

	if (!philo)
		return (-1);
	rfork_i = (philo->philo_id - 2 + philo->n_of_philos) % philo->n_of_philos;
	if (philo->state == PHILO_THINK && philo->rfork_mutex == 0)
	{
		if (pthread_mutex_lock(&philo->forks[rfork_i]) == 0)
		{
			pthread_mutex_lock(&philo->forks[rfork_i]);
			philo->rfork_mutex = &philo->forks[rfork_i];
			print_status(philo, "has taken right fork");
			return (0);
		}
	}
	return (-1);
}

int	check_alive(t_philo *philosopher)
{
	struct timeval	current_time;
	long			ctime_ms;
	long			time_diff;

	gettimeofday(&current_time, NULL);
	ctime_ms = current_time.tv_sec * 1000;
	if (philosopher->lt_eat == 0)
		time_diff = ctime_ms - philosopher->matrix_start;
	else
		time_diff = ctime_ms - philosopher->lt_eat;
	if (time_diff >= 0)
		return (1);
	else
		return (0);
}
