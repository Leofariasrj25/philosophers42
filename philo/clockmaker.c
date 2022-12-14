/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clockmaker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:57:57 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/13 21:51:06 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <unistd.h>

unsigned int	elapsed_time_since(unsigned int timestamp_ms)
{
	unsigned int	et;

	et = getcurrtime_ms() - timestamp_ms;
	return (et);
}

int	tstamp_cmp_ms(unsigned int ts1, unsigned int ts2)
{
	if (ts2 > ts1)
		return (1);
	if (ts2 < ts1)
		return (-1);
	return (0);
}

unsigned int	getcurrtime_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((unsigned int)(current_time.tv_sec * 1000));
}

void	micro_sleep(unsigned long duration)
{
	unsigned long	sleep_cycle;

	sleep_cycle = 0;
	while (sleep_cycle < duration)
	{
		usleep(5);
		sleep_cycle += 5;
	}
}
