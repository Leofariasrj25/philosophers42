/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clockmaker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:57:57 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/15 17:09:11 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <unistd.h>

long	elapsed_time_since(unsigned int timestamp_ms)
{
	long	et;

	et = getcurrtime_ms() - timestamp_ms;
	return (et);
}

long	getcurrtime_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((unsigned int)(current_time.tv_sec * 1000));
}

void	micro_sleep(long duration)
{
	long	start_time;
	
	start_time = getcurrtime_ms();
	while (start_time + duration > getcurrtime_ms())
		usleep(20);
	return ;
}
