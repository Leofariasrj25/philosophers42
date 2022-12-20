/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_reloaded.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 22:00:34 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/19 23:00:00 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

int	check_is_dinner_over(t_philo *philo)
{
	int	is_dinner_over;

	pthread_mutex_lock(philo->banquet->dinner_mutex);
	if ((philo->min_meals != -1 && philo->banquet->total_meals != 0) \
		&& philo->banquet->curr_meals == philo->banquet->total_meals)
	{
		philo->banquet->is_over = 1;
	}
	if (philo->banquet->is_over == 1)
		is_dinner_over = 1;
	else
		is_dinner_over = 0;
	pthread_mutex_unlock(philo->banquet->dinner_mutex);
	return (is_dinner_over);
}
