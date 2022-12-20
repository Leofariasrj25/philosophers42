/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clockmaker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:57:57 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/20 18:45:56 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <sys/time.h>
#include <unistd.h>

long	get_timestamp_ms(long time_start_ms)
{
	return (get_currtime_ms() - time_start_ms);
}

long	get_currtime_ms(void)
{
	struct timeval	current_time;
	long			ctime;

	gettimeofday(&current_time, NULL);
	ctime = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (ctime);
}

int	micro_sleep(long duration, t_philo *philo)
{
	long	start_time;
	long	ret_code;

	start_time = get_currtime_ms();
	while (start_time + duration >= get_currtime_ms())
	{
		ret_code = check_alive(philo);
		if (ret_code == PHILO_DEAD)
			return (PHILO_DEAD);
		else if (ret_code == MATRIX_END)
			return (MATRIX_END);
	}
	return (0);
}
