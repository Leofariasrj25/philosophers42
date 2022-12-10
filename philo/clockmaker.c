/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clockmaker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:57:57 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/09 18:57:08 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

unsigned int	elapsed_time_ms(unsigned int timestamp_ms)
{
	struct timeval	current_time;
	unsigned int	et;

	gettimeofday(&current_time, NULL);
	et = ((current_time.tv_sec * 1000) - timestamp_ms);
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

unsigned int	getcurrtime_ms()
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((unsigned int)(current_time.tv_sec * 1000));
}
