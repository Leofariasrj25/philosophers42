/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:29:01 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/19 22:57:54 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <unistd.h>

int	philo_eat_meal(t_philo *philosopher)
{
	long	lt_eat;
	int		ret_code;

	if (has_forks(philosopher))
	{
		print_status(philosopher, "is eating", PHILO_EAT);
		if (add_total_meals(philosopher) == 1)
		{
			philosopher->state = PHILO_DEAD;
			return (-1);
		}
		lt_eat = get_currtime_ms();
		ret_code = micro_sleep(philosopher->tt_eat, philosopher);
		if (ret_code == PHILO_DEAD)
		{
			philosopher->state = PHILO_DEAD;
			return (PHILO_DEAD);
		}
		else if (ret_code == MATRIX_END)
			return (MATRIX_END);
		philosopher->lt_eat = lt_eat;
		return (philo_sleep(philosopher));
	}
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	int	ret_code;

	if (!philo)
		return (-1);
	philo_put_forks_down(philo);
	print_status(philo, "is sleeping", PHILO_SLEEP);
	philo->state = PHILO_SLEEP;
	ret_code = micro_sleep(philo->tt_sleep, philo);
	if (ret_code == PHILO_DEAD)
	{
		philo->state = PHILO_DEAD;
		return (PHILO_DEAD);
	}
	else if (ret_code == MATRIX_END)
		return (MATRIX_END);
	philo->state = PHILO_THINK;
	return (PHILO_THINK);
}

void	philo_think(t_philo *philo)
{
	if ((philo->lfork_mutex == NULL && philo->rfork_mutex == NULL) \
		&& philo->state == PHILO_THINK)
	{
		print_status(philo, "is thinking", PHILO_THINK);
	}
}

int	has_forks(t_philo *philosopher)
{
	if ((philosopher->lfork_mutex != NULL && philosopher->rfork_mutex != NULL) \
		&& (philosopher->state == PHILO_THINK))
		return (1);
	else
		return (0);
}

int	check_alive(t_philo *philosopher)
{
	long	checkpoint;
	long	c_time;

	if (check_is_dinner_over(philosopher) == 1)
		return (MATRIX_END);
	if (philosopher->lt_eat == 0)
		checkpoint = philosopher->matrix_start;
	else
		checkpoint = philosopher->lt_eat;
	c_time = get_currtime_ms();
	if (c_time < (checkpoint + philosopher->tt_die))
		return (1);
	else
		return (PHILO_DEAD);
}
