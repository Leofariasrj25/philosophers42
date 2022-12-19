/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clockmaker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:57:57 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/18 21:37:55 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
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
	ctime = (current_time.tv_sec * 1000000) + (current_time.tv_usec);
	ctime = ctime / 1000;
	return (ctime);
}

void	micro_sleep(long duration, t_philo *philo)
{
	long	start_time;
	
	start_time = get_currtime_ms();
	while (start_time + duration >= get_currtime_ms() && check_alive(philo)) 
		usleep(duration / 5);
	return ;
}
