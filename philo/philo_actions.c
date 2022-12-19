/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:29:01 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/19 02:49:24 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <unistd.h>

int	philo_eat_meal(t_philo *philosopher)
{
	long	lt_eat;

	if ((philosopher->lfork_mutex != NULL && philosopher->rfork_mutex != NULL) \
		&& (philosopher->state == PHILO_THINK))
	{
		lt_eat = get_currtime_ms();
		print_status(philosopher, "is eating", PHILO_EAT);
		if (philosopher->lt_eat == 0)
		{
			if (philosopher->matrix_start + philosopher->tt_die > philosopher->matrix_start + philosopher->tt_eat)
				micro_sleep(philosopher->tt_eat, philosopher); 
			else
			{
				/*micro_sleep(philosopher->tt_die, philosopher);
				philosopher->state = PHILO_DEAD;
				print_status(philosopher, "is dead", PHILO_DEAD);
				return (-1);*/
				micro_sleep(philosopher->lt_eat + philosopher->tt_eat - (philosopher->lt_eat + philosopher->tt_die), philosopher);
				philosopher->state = PHILO_DEAD;
				return (-1);
			}
		}
		else
		{
			if (philosopher->lt_eat + philosopher->tt_die > philosopher->lt_eat + philosopher->tt_eat)
				micro_sleep(philosopher->tt_eat, philosopher); 
			else
			{
				micro_sleep(philosopher->lt_eat + philosopher->tt_eat - (philosopher->lt_eat + philosopher->tt_die), philosopher);
				philosopher->state = PHILO_DEAD;
				//print_status(philosopher, "is dead", PHILO_DEAD);
				return (-1);
			}
		}
		philosopher->lt_eat = lt_eat;
		return (philo_sleep(philosopher));
	}
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (!philo)
		return (-1);
	philo_put_forks_down(philo);
	print_status(philo, "is sleeping", PHILO_SLEEP);
	philo->state = PHILO_SLEEP;
	if (check_alive(philo) == 0)
	{
		philo->state = PHILO_DEAD;
		return (PHILO_DEAD);
	}
	if (philo->lt_eat + philo->tt_sleep < philo->lt_eat + philo->tt_die)
	{
		micro_sleep(philo->tt_sleep, philo);
		philo->state = PHILO_THINK;
		return (PHILO_THINK);
	}
	else
	{
		micro_sleep(philo->lt_eat + philo->tt_sleep - (philo->lt_eat + philo->tt_die), philo);	
		philo->state = PHILO_DEAD;
		return (PHILO_DEAD);
	}
}

int	philo_take_lfork(t_philo *philosopher)
{	
	if (!philosopher)
		return (-1);
	if (philosopher->state == PHILO_THINK && philosopher->lfork_mutex == NULL)
	{
		if (pthread_mutex_lock(&philosopher->forks[philosopher->philo_id - 1]) == 0)
		{
			if (check_is_dinner_over(philosopher) == 1)
				return (-1);
			if (check_alive(philosopher) == 0)
				return (PHILO_DEAD);
			philosopher->lfork_mutex = &philosopher->forks[philosopher->philo_id - 1];
			print_status(philosopher, "has taken left fork", PHILO_THINK);
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
	if (philo->state == PHILO_THINK && philo->rfork_mutex == NULL)
	{
		if (pthread_mutex_lock(&philo->forks[get_right_index(philo)]) == 0)
		{
			if (check_is_dinner_over(philo) == 1)
				return (-1);
			if (check_alive(philo) == 0)
				return (PHILO_DEAD);
			philo->rfork_mutex = &philo->forks[get_right_index(philo)];
			print_status(philo, "has taken right fork", PHILO_THINK);
			return (1);
		}
	}
	return (0);
}

/*	printf("philospher->lt_eat: %ld\n", philosopher->lt_eat);
	printf("philospher->tt_die: %ld\n", philosopher->tt_die);
	printf("time_diff: %ld\n", time_diff); */
int	check_alive(t_philo *philosopher)
{
	long	time_diff;

	if (check_is_dinner_over(philosopher) == 1)
		return (-1);
	pthread_mutex_lock(philosopher->print_mutex);
	if (philosopher->lt_eat == 0)
		time_diff = get_currtime_ms() - philosopher->matrix_start;
	else
		time_diff = get_currtime_ms() - philosopher->lt_eat;
	if (time_diff < philosopher->tt_die)
	{
		pthread_mutex_unlock(philosopher->print_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philosopher->print_mutex);
		return (0);
	}
}

int	philo_put_forks_down(t_philo *philosopher)
{
	if (philosopher->philo_id == philosopher->n_of_philos)
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
	}
	else 
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
	}
	return (0);
}

int philo_take_forks(t_philo *philosopher)
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
